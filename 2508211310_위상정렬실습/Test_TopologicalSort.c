#include "Graph.h"
#include "TopologicalSort.h"

int main() {
	Node* SortedList = NULL;
	Node* CurrentNode = NULL;

	// 그래프 생성
	Graph* graph = CreateGraph();

	// 정점 생성

	Vertex* A = CreateVertex("C언어");
	Vertex* B = CreateVertex("자료구조");
	Vertex* C = CreateVertex("C++언어");
	Vertex* D = CreateVertex("알고리즘");
	Vertex* E = CreateVertex("C#언어");
	Vertex* F = CreateVertex("언리얼엔진");
	Vertex* G = CreateVertex("코딩테스트");
	Vertex* H = CreateVertex("Unity");
	Vertex* I = CreateVertex("포트폴리오");
	Vertex* J = CreateVertex("취업");

	// 그래프에 정점을 추가
	AddVertex(graph, A);
	AddVertex(graph, B);
	AddVertex(graph, C);
	AddVertex(graph, D);
	AddVertex(graph, E);
	AddVertex(graph, F);
	AddVertex(graph, G);
	AddVertex(graph, H);
	AddVertex(graph, I);
	AddVertex(graph, J);

	// 정점과 정점을 간선으로 잇기
	AddEdge(A, CreateEdge(A, C, 0));

	AddEdge(B, CreateEdge(B, D, 0));

	AddEdge(C, CreateEdge(C, E, 0));
	AddEdge(C, CreateEdge(C, F, 0));

	AddEdge(D, CreateEdge(D, H, 0));
	AddEdge(D, CreateEdge(D, F, 0));
	AddEdge(D, CreateEdge(D, G, 0));

	AddEdge(E, CreateEdge(E, H, 0));

	AddEdge(F, CreateEdge(F, I, 0));

	AddEdge(G, CreateEdge(G, J, 0));

	AddEdge(H, CreateEdge(H, I, 0));

	AddEdge(I, CreateEdge(I, J, 0));



	// 위상정렬
	TopologicalSort(graph->Vertices, &SortedList);

	printf("Topological Sort Result : ");
	CurrentNode = SortedList;

	while (CurrentNode != NULL) {
		printf("%s ", CurrentNode->Data->Data);
		CurrentNode = CurrentNode->NextNode;
	}
	printf("\n");


	// 리스트 소멸
	while (SortedList != NULL) {
		CurrentNode = SortedList;
		SortedList = SortedList->NextNode;

		SLL_DestroyNode(CurrentNode);
	}

	// 그래프 소멸
	DestroyGraph(graph);

	return 0;
}