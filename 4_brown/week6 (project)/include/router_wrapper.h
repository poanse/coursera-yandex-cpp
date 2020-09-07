#pragma once

#include <router.h>
#include <route.h>
#include <distances.h>

#include <string>
#include <vector>

// typedef double WeightFunction (const std::string&, const std::string&);
using Stops = std::unordered_map<std::string, StopPtr>;
using Routes = std::unordered_map<std::string, RoutePtr>;

struct Vertex {
	std::string stop;
	std::optional<std::string> bus;
	std::optional<bool> is_start;

	bool operator==(const Vertex& other) const;
};

namespace std {
	template<>
	struct hash<Vertex> {
		size_t operator()(const Vertex& v) const {
			size_t v1 = std::hash<std::string>()(v.stop);
			size_t v2 = std::hash<std::optional<std::string>>()(v.bus);
			size_t v3 = std::hash<std::optional<bool>>()(v.is_start);
			size_t h = v1 * 3517 + v2;
			h = h * 3517 + v3;
			return h;
		}
	};
}

struct RouteStep {
	const std::string& stop_from;
	const std::string& stop_to;
	const std::string& bus;
	double weight;
	RouteStep(const std::string& sf, const std::string& st, const std::string& b, double w)
		: stop_from(sf), stop_to(st), bus(b), weight(w) { }
};

class RouterWrapper {
public:
  RouterWrapper(const Stops&, const Routes&, const Distances&, const RoutingSettings&);
	std::optional<std::vector<RouteStep>> GetRoute(const std::string& stop1, const std::string& stop2);
private:
	using VertexId = size_t;
	const Distances& distances;
	const RoutingSettings& routing_settings;
	std::unordered_map<Vertex, VertexId> VertexIds;
	std::vector<Vertex> vertexes;
	std::vector<Graph::Edge<double>> edges;
	std::optional<Graph::DirectedWeightedGraph<double>> graph;
	std::optional<Graph::Router<double>> router;
private:
	double GetEdgeWeight(const std::string& stop1, const std::string& stop2) const;
	const Graph::Edge<double>& GetEdgeById(Graph::EdgeId edge_id) const { return edges[edge_id]; }
	const Vertex& GetVertexById(VertexId v_id) const { return vertexes[v_id]; }
	const std::vector<Graph::Edge<double>>& GetEdges() const { return edges;	}
	size_t GetVertexCount() const { return vertexes.size();	}

	size_t AddShallowVertex(std::string stop);

	size_t AddVertex(const std::string& stop, std::optional<std::string> bus, 
		std::optional<bool> is_start = std::nullopt);

	void AddEdge(VertexId from, VertexId to, double weight) {
		edges.push_back({from, to, weight});
	}

	void AddRoute(const std::string& bus, const Route::Info& info);
	void AddCircularRoute(const std::string& bus, const Route::Info& info);
	void AddLinearRoute(const std::string& bus, const Route::Info& info);
};
