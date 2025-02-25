
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 512
#define MIN_VERTICES 256
#define MAX_EDGES (MAX_VERTICES * 10)  // 每个节点最多连接8个节点，最多生成的边数
#define MAX_WEIGHT 1000  // 边的权重最大值

// 创建一个随机的图数据集
void generate_graph(int *row_ptr, int *col_idx, int *data, int *num_vertices, int *num_edges) {
    // 随机生成节点数
    *num_vertices = rand() % (MAX_VERTICES - MIN_VERTICES + 1) + MIN_VERTICES;

    // 随机生成边数（最大为顶点数的8倍）
    *num_edges = rand() % (MAX_EDGES - *num_vertices + 1) + *num_vertices;

    int edge_count = 0;

    // 确保每个节点最多有8个邻接节点
    for (int i = 0; i < *num_vertices; i++) {
        row_ptr[i] = edge_count;
        int neighbors = rand() % 4 + 7; 
        for (int j = 0; j < neighbors && edge_count < *num_edges; j++) {
            int neighbor = rand() % *num_vertices;  // 随机选择邻接节点
            // 避免自环
            if (neighbor != i) {
                col_idx[edge_count] = neighbor;
                data[edge_count] = rand() % MAX_WEIGHT + 1;  // 随机生成边权重
                edge_count++;
            }
        }
    }

    // 更新最后一个节点的结束位置
    row_ptr[*num_vertices] = edge_count;  // 最后一行的结束位置
}

// 将图数据写入文件
void write_graph_to_file(const char *filename, int *row_ptr, int *col_idx, int *data, int num_vertices, int num_edges) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // 写入顶点和边数
    fprintf(file, "Number of vertices: %d\n", num_vertices);
    fprintf(file, "Number of edges: %d\n", num_edges);

    // 写入 row_ptr[]
    fprintf(file, "row_ptr[] = {");
    for (int i = 0; i < num_vertices; i++) {
        fprintf(file, "%d, ", row_ptr[i]);
    }
    fprintf(file, "%d}\n", row_ptr[num_vertices]);

    // 写入 col_idx[]
    fprintf(file, "col_idx[] = {");
    for (int i = 0; i < num_edges; i++) {
        fprintf(file, "%d, ", col_idx[i]);
    }
    fprintf(file, "}\n");

    // 写入 data[]
    fprintf(file, "data[] = {");
    for (int i = 0; i < num_edges; i++) {
        fprintf(file, "%d, ", data[i]);
    }
    fprintf(file, "}\n");

    fclose(file);
    printf("Graph data has been written to %s\n", filename);
}

int main() {
    srand(time(NULL));  // 设置随机种子

    int row_ptr[MAX_VERTICES + 1];
    int col_idx[MAX_EDGES];
    int data[MAX_EDGES];

    int num_vertices, num_edges;

    // 生成图数据集
    generate_graph(row_ptr, col_idx, data, &num_vertices, &num_edges);

    // 写入图数据到文件
    const char *filename = "graph_data.txt";
    write_graph_to_file(filename, row_ptr, col_idx, data, num_vertices, num_edges);

    return 0;
}
