#include "Graph.h"
#include "TopologicalSort.h"

int main() {
	Node* SortedList = NULL;
	Node* CurrentNode = NULL;

	// �׷��� ����
	Graph* graph = CreateGraph();

	// ���� ����

	Vertex* A = CreateVertex("C���");
	Vertex* B = CreateVertex("�ڷᱸ��");
	Vertex* C = CreateVertex("C++���");
	Vertex* D = CreateVertex("�˰���");
	Vertex* E = CreateVertex("C#���");
	Vertex* F = CreateVertex("�𸮾���");
	Vertex* G = CreateVertex("�ڵ��׽�Ʈ");
	Vertex* H = CreateVertex("Unity");
	Vertex* I = CreateVertex("��Ʈ������");
	Vertex* J = CreateVertex("���");

	// �׷����� ������ �߰�
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

	// ������ ������ �������� �ձ�
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



	// ��������
	TopologicalSort(graph->Vertices, &SortedList);

	printf("Topological Sort Result : ");
	CurrentNode = SortedList;

	while (CurrentNode != NULL) {
		printf("%s ", CurrentNode->Data->Data);
		CurrentNode = CurrentNode->NextNode;
	}
	printf("\n");


	// ����Ʈ �Ҹ�
	while (SortedList != NULL) {
		CurrentNode = SortedList;
		SortedList = SortedList->NextNode;

		SLL_DestroyNode(CurrentNode);
	}

	// �׷��� �Ҹ�
	DestroyGraph(graph);

	return 0;
}