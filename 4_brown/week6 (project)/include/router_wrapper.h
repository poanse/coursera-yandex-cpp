#pragma once

#include <router.h>
#include <route.h>
#include <distances.h>

#include <string>
#include <vector>
#include <memory>

class RouterWrapper {
public:
	struct RouteStep {
		const std::string& stop_from;
		const std::string& stop_to;
		const std::string& bus;
		double weight;
		int stop_count;
	};
	using VertexId = size_t;
	using EdgeId = size_t;
	using Stops  = std::unordered_map<std::string, StopPtr>;
	using Routes = std::unordered_map<std::string, RoutePtr>;
	using Vertex = std::string;

  RouterWrapper(const Stops&, const Routes&, const Distances&, const RoutingSettings&);
	std::optional<std::vector<RouteStep>> GetRoute(const std::string& stop1, const std::string& stop2);

private:
	const Distances& distances;
	const RoutingSettings& routing_settings;
	std::vector<Vertex> vertexes;
	std::vector<Graph::Edge<double>> edges;
	std::unordered_map<Vertex, VertexId> VertexIds;
	std::unordered_map<EdgeId, std::pair<std::string, int>> BusByEdgeId; // bus and stop_count
	std::unique_ptr<Graph::DirectedWeightedGraph<double>> graph;
	std::unique_ptr<Graph::Router<double>> router;

private:
	const Graph::Edge<double>& GetEdgeById(Graph::EdgeId edge_id) const { 
		return edges[edge_id]; 
	}
	const Vertex& GetVertexById(VertexId v_id) const { 
		return vertexes[v_id];
	}
	const std::vector<Graph::Edge<double>>& GetEdges() const {
		return edges;
	}
	size_t GetVertexCount() const {
		return vertexes.size();
	}

	VertexId AddStop(const std::string& stop);
	double GetWeightFromDistance(double) const;

	template<typename It>
	void AddEdge(It from, It to, const std::string& bus);

	void AddRoute(const Route::Info& info);
	void AddCircularRoute(const Route::Info& info);
	void AddLinearRoute(const Route::Info& info);
};
