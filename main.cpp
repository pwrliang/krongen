//
// Created by liang on 3/16/18.
//
#include <gflags/gflags.h>
#include <set>
#include "graph_generator.h"
#include "make_graph.h"

DEFINE_int32(scale, 16, "number of vertices = 2^scale");
DEFINE_int32(edge_factor, 48, "edges = edge_factor * number of vertices");
DEFINE_string(output, "", "output path");
DEFINE_bool(directed, false, "generate directed graph");

int main(int argc, char **argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    int log_numverts = FLAGS_scale;
    int64_t nverts = (int64_t) 1 << log_numverts;
    int64_t desired_nedges = FLAGS_edge_factor * (int64_t) nverts;
    int64_t max_edges = nverts * (nverts - 1) / 2;
    int64_t nedges;
    packed_edge *result;


    if (nverts >= UINT32_MAX) {
        printf("the number of vertices can not more than:%u\n", UINT32_MAX);
        return 1;
    }

    if (desired_nedges > max_edges) {
        printf("vertices: %lld desired edges: %lld, but edges can not more than: %lld\n",
               (long long) nverts,
               (long long) desired_nedges,
               (long long) max_edges);
        return 1;
    }


    FILE *fp = fopen(FLAGS_output.data(), "w");
    if (fp == nullptr) {
        printf("CAN NOT OPEN FILE %s\n", FLAGS_output.data());
        exit(1);
    }

    printf("graph info: scale:%d edge_factor:%d %s output:%s\n",
           FLAGS_scale, FLAGS_edge_factor, FLAGS_directed ? "directed" : "undirected", FLAGS_output.data());

    make_graph(log_numverts, desired_nedges, 1, 2, &nedges, &result);

    std::set<std::pair<uint32_t, uint32_t>> edges;

    for (int64_t k = 0; k < nedges; ++k) {
        const int64_t i = get_v0_from_edge(&result[k]);
        const int64_t j = get_v1_from_edge(&result[k]);
        if (i == j) continue;
        edges.insert({i, j});
        if (!FLAGS_directed)
            edges.insert({j, i});
    }

    printf("num_verts:%u, desired_edges:%lld num_edges:%lu\n", nverts, (long long) desired_nedges, edges.size());
    printf("writing...\n");

    for (const auto &edge : edges) {
        fprintf(fp, "%u %u\n", edge.first, edge.second);
    }

    free(result);
    fclose(fp);
    printf("write operation done\n");
    return 0;
}