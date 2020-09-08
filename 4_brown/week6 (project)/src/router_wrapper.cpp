#include "router_wrapper.h"

#include <iostream>

using namespace std;

// bool Vertex::operator==(const Vertex& other) const {
//   return stop == other.stop &&
//           bus == other.bus &&
//           is_start == other.is_start;
// }

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
	graph.emplace(GetVertexCount());
	for (const auto& edge : GetEdges()) {
		graph.value().AddEdge(edge);
	}
  router.emplace(graph.value());
}


optional<vector<RouteStep>> RouterWrapper::GetRoute(const string& stop1, const string& stop2) 
{
  VertexId from = VertexIds.at(stop1);
  VertexId to = VertexIds.at(stop2);
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
      const auto& [bus, stop_count] = BusByEdgeId.at(edge_id);
      steps.push_back({stop_from, stop_to, bus, edge.weight, stop_count});
    }
    return steps;
  }
  return nullopt;
}


size_t RouterWrapper::AddStop(const string& stop) 
{
  Vertex vertex = stop;
  vertexes.push_back(vertex);
  size_t id = vertexes.size() - 1;
  VertexIds[move(vertex)] = id;
  return id; 
}

// size_t RouterWrapper::AddVertex(
//     const string& stop, 
//     optional<string> bus, 
//     optional<bool> is_start) 
// {
//   Vertex vertex = {stop, move(bus), is_start};
//   vertexes.push_back(vertex);
//   size_t id = vertexes.size() - 1;
//   VertexIds[move(vertex)] = id;
//   size_t id_shallow = VertexIds.at({stop, nullopt, nullopt});
//   AddEdge(id_shallow, id, routing_settings.bus_wait_time);
//   AddEdge(id, id_shallow, 0);
//   return id; 
// }

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
  // Distances route_distances = CreateTemporaryDistances(info);
  const auto& stops = info.stops;
  for (auto it = stops.begin(); it != stops.end(); it++) {
    for (auto it2 = next(it); it2 != stops.end(); it2++) {
      AddEdge(it, it2, info.bus);
    }
  }
}

void RouterWrapper::AddLinearRoute(const Route::Info& info) 
{
  // Distances route_distances = CreateTemporaryDistances(info);
  const auto& stops = info.stops;
  for (auto it = stops.begin(); it != stops.end(); it++) {
    for (auto it2 = next(it); it2 != stops.end(); it2++) {
      AddEdge(it, it2, info.bus);
      // AddEdge(it2, it, info.bus);
    }
  }
  for (auto it = stops.rbegin(); it != stops.rend(); it++) {
    for (auto it2 = next(it); it2 != stops.rend(); it2++) {
      AddEdge(it, it2, info.bus);
    }
  }
}

Distances RouterWrapper::CreateTemporaryDistances(const Route::Info& info) const
{
  Distances m;
  const auto& stops = info.stops;
  for (size_t i = 0; i+1 < stops.size(); i++) {
    m[{stops[i], stops[i+1]}] = distances.GetDistance(stops[i], stops[i+1]);
  }
  for (size_t i = 0; i < stops.size(); i++) {
    for (size_t delta = 2; i+delta < stops.size(); delta++) {
      double candidate = 0;
      for (size_t k = 0; k < delta; k++) {
        candidate += m.at({stops.at(i+k), stops.at(i+k+1)});
      }
      // auto candidate = m.at({stops[i], stops[i+delta-1]}) + m.at({stops[i+delta-1], stops[i+delta]});
      const pair<string, string> target {stops[i], stops[i+delta]};
      // if (m.find(target) == m.end() || (m.at(target) > candidate)) {
      //   m[target] = candidate;
      // }
      if (m.find(target) == m.end()) {
        m[target] = candidate;
      }
    }
  }
  return m;
}

double RouterWrapper::GetWeightFromDistance(double distance) const {
	auto velocity = routing_settings.bus_velocity * 1000 / 60;
	return distance / velocity + routing_settings.bus_wait_time;
}

double RouterWrapper::GetEdgeWeight(const string& stop1, const string& stop2) const {
	auto distance = distances.GetDistance(stop1, stop2);
	auto velocity = routing_settings.bus_velocity * 1000 / 60;
	return distance / velocity;
}
// void RouterWrapper::AddEdge(Vertex from, Vertex to, const Distances& route_distances, const std::string& bus, int stop_count) 
// {
//   VertexId from_id = VertexIds.at(from);
//   VertexId to_id = VertexIds.at(to);
//   double distance = route_distances.GetDistance(from, to);
//   double weight = GetWeightFromDistance(distance);
//   Graph::Edge<double> edge = {from_id, to_id, weight};
//   edges.push_back(edge);
//   BusByEdgeId[edges.size() - 1] = {bus, stop_count};
// }

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