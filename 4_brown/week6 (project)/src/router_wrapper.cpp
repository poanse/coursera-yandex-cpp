#include "router_wrapper.h"

#include <iostream>

using namespace std;

RouterWrapper::RouterWrapper(
    const Stops& stops,
    const Routes& routes, 
    const Distances& distances_, 
    const RoutingSettings& routing_settings_)
  : distances(distances_)
  , routing_settings(routing_settings_)
{
  for (auto& stop : stops) {
		AddStop(stop.first);
	}
	for (const auto& [bus, route_ptr] : routes) {
		const auto& info = *(route_ptr->info);
    AddRoute(info);
	}
	graph = make_unique<Graph::DirectedWeightedGraph<double>>(GetVertexCount());
	for (const auto& edge : GetEdges()) {
		graph->AddEdge(edge);
	}
  router = make_unique<Graph::Router<double>>(*graph);
}

optional<vector<RouterWrapper::RouteStep>> RouterWrapper::GetRoute(const string& stop1, const string& stop2) 
{
  VertexId from = VertexIds.at(stop1);
  VertexId to = VertexIds.at(stop2);
  vector<RouteStep> steps;
  if (from == to) return steps;
  std::optional<Graph::Router<double>::RouteInfo> route_info = router->BuildRoute(from, to);
  if (route_info) {
    steps.reserve(route_info.value().edge_count);
    for (size_t edge_idx = 0; edge_idx < route_info.value().edge_count; edge_idx++) {
      Graph::EdgeId edge_id = router->GetRouteEdge(route_info.value().id, edge_idx);
      const Graph::Edge<double>& edge = GetEdgeById(edge_id);
      const Vertex& stop_from = GetVertexById(edge.from);
      const Vertex& stop_to = GetVertexById(edge.to);
      const auto& [bus, stop_count] = BusByEdgeId.at(edge_id);
      steps.push_back({stop_from, stop_to, bus, edge.weight, stop_count});
    }
    return steps;
  }
  return nullopt;
}

RouterWrapper::VertexId RouterWrapper::AddStop(const string& stop) 
{
  Vertex vertex = stop;
  vertexes.push_back(vertex);
  size_t id = vertexes.size() - 1;
  VertexIds[move(vertex)] = id;
  return id; 
}

void RouterWrapper::AddRoute(const Route::Info& info) 
{
  if (info.is_circular) {
    AddCircularRoute(info);
  } else {
    AddLinearRoute(info);
  }
}

void RouterWrapper::AddCircularRoute(const Route::Info& info) 
{
  const auto& stops = info.stops;
  for (auto it = stops.begin(); it != stops.end(); it++) {
    for (auto it2 = next(it); it2 != stops.end(); it2++) {
      AddEdge(it, it2, info.bus);
    }
  }
}

void RouterWrapper::AddLinearRoute(const Route::Info& info) 
{
  const auto& stops = info.stops;
  for (auto it = stops.begin(); it != stops.end(); it++) {
    for (auto it2 = next(it); it2 != stops.end(); it2++) {
      AddEdge(it, it2, info.bus);
    }
  }
  for (auto it = stops.rbegin(); it != stops.rend(); it++) {
    for (auto it2 = next(it); it2 != stops.rend(); it2++) {
      AddEdge(it, it2, info.bus);
    }
  }
}

double RouterWrapper::GetWeightFromDistance(double distance) const 
{
	auto velocity = routing_settings.bus_velocity * 1000 / 60;
	return distance / velocity + routing_settings.bus_wait_time;
}

template<typename It>
void RouterWrapper::AddEdge(It from, It to, const std::string& bus) 
{
  VertexId from_id = VertexIds.at(*from);
  VertexId to_id = VertexIds.at(*to);
  auto stop_count = std::distance(from, to);
  double distance = 0;
  for (auto it = from; it != to; it++) {
    distance += distances.GetDistance(*it, *next(it));
  }
  double weight = GetWeightFromDistance(distance);
  Graph::Edge<double> edge = {from_id, to_id, weight};
  edges.push_back(edge);
  BusByEdgeId[edges.size() - 1] = {bus, stop_count};
}