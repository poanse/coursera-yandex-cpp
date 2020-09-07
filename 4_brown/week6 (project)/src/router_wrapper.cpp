#include "router_wrapper.h"

#include <iostream>

using namespace std;

bool Vertex::operator==(const Vertex& other) const {
  return stop == other.stop &&
          bus == other.bus &&
          is_start == other.is_start;
}

RouterWrapper::RouterWrapper(
    const Stops& stops,
    const Routes& routes, 
    const Distances& distances_, 
    const RoutingSettings& routing_settings_)
  : distances(distances_)
  , routing_settings(routing_settings_)
{
  for (auto& stop : stops) {
		AddShallowVertex(stop.first);
	}
  // cerr << "shallow vertexes added" << endl;
	for (const auto& [bus, route_ptr] : routes) {
		const auto& info = *(route_ptr->info);
		if (info.stops.empty()) {
			continue;
		}
		AddRoute(bus, info);
	}
  // cerr << "routes added" << endl;
	graph.emplace(GetVertexCount());
  // cerr << "graph emplaces" << endl;
	for (const auto& edge : GetEdges()) {
		graph.value().AddEdge(edge);
	}
  // cerr << "graph edges added" << endl;
  router.emplace(graph.value());
  // cerr << "router emplaced" << endl;
}


optional<vector<RouteStep>> RouterWrapper::GetRoute(const string& stop1, const string& stop2) 
{
  VertexId from = VertexIds.at({stop1, nullopt, nullopt});
  VertexId to = VertexIds.at({stop2, nullopt, nullopt});
  vector<RouteStep> steps;
  if (from == to) return steps;
  std::optional<Graph::Router<double>::RouteInfo> route_info = router.value().BuildRoute(from, to);
  if (route_info) {
    steps.reserve(route_info.value().edge_count);
    for (size_t edge_idx = 0; edge_idx < route_info.value().edge_count; edge_idx++) {
      Graph::EdgeId edge_id = router.value().GetRouteEdge(route_info.value().id, edge_idx);
      const Graph::Edge<double>& edge = GetEdgeById(edge_id);
      const Vertex& stop_from = GetVertexById(edge.from);
      const Vertex& stop_to = GetVertexById(edge.to);
      steps.emplace_back(
        stop_from.stop, 
        stop_to.stop, 
        (stop_from.bus ? stop_from.bus.value() : stop_to.bus.value()), 
        edge.weight
      );
    }
    return steps;
  }
  return nullopt;
}


size_t RouterWrapper::AddShallowVertex(string stop) 
{
  Vertex vertex = {move(stop), nullopt, nullopt};
  vertexes.push_back(vertex);
  size_t id = vertexes.size() - 1;
  VertexIds[move(vertex)] = id;
  return id; 
}

size_t RouterWrapper::AddVertex(
    const string& stop, 
    optional<string> bus, 
    optional<bool> is_start) 
{
  Vertex vertex = {stop, move(bus), is_start};
  vertexes.push_back(vertex);
  size_t id = vertexes.size() - 1;
  VertexIds[move(vertex)] = id;
  size_t id_shallow = VertexIds.at({stop, nullopt, nullopt});
  AddEdge(id_shallow, id, routing_settings.bus_wait_time);
  AddEdge(id, id_shallow, 0);
  return id; 
}

void RouterWrapper::AddRoute(
    const string& bus, 
    const Route::Info& info) 
{
  if (info.is_circular) {
    AddCircularRoute(bus, info);
  } else {
    AddLinearRoute(bus, info);
  }
}

void RouterWrapper::AddCircularRoute(
    const string& bus, 
    const Route::Info& info) 
{
  // add first
  AddVertex(info.stops.front(), bus, true);
  // add others
  auto it = next(info.stops.begin());
  optional<bool> is_start = nullopt;
  for (; it != info.stops.end(); it++) {
    if (it == prev(info.stops.end())) is_start = false;
    size_t id = AddVertex(*it, bus, is_start);
    AddEdge(id-1, id, GetEdgeWeight(*prev(it), *it));
  }
}

void RouterWrapper::AddLinearRoute(
    const string& bus, 
    const Route::Info& info) 
{
  // add first
  AddVertex(info.stops.front(), bus);
  // add others
  for (auto it = next(info.stops.begin()); it != info.stops.end(); it++) {
    size_t id = AddVertex(*it, bus);
    AddEdge(id-1, id, GetEdgeWeight(*prev(it), *it));
    AddEdge(id, id-1, GetEdgeWeight(*it, *prev(it)));
  }
}


double RouterWrapper::GetEdgeWeight(const string& stop1, const string& stop2) const {
	auto distance = distances.GetDistance(stop1, stop2);
	auto velocity = routing_settings.bus_velocity * 1000 / 60;
	return distance / velocity;
}