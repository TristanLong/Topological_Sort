#include "iostream"
#include "fstream"
#include "queue"
using namespace std;

const int MAX = 20;

struct maTrix {
	int maTranKe[MAX][MAX];
	int soDinh;
};

void readFile(maTrix& mtk) {
	ifstream inFile("Text.txt");
	if (!inFile.is_open()) {
		cout << "\nKhong the mo tep";
		return;
	}

	inFile >> mtk.soDinh;
	for (int i = 0; i < mtk.soDinh; i++) {
		for (int j = 0; j < mtk.soDinh; j++) {
			inFile >> mtk.maTranKe[i][j];
		}
	}
	inFile.close();
}

void outputMaTrix(maTrix mtk) {
	cout << "\nMA TRAN KE: " << endl;
	for (int i = 0; i < mtk.soDinh; i++) {
		for (int j = 0; j < mtk.soDinh; j++) {
			cout << mtk.maTranKe[i][j] << "\t";
		}
		cout << endl;
	}
}

int tinhBacVao(maTrix mtk, int u) {
	int count = 0;
	for (int i = 0; i < mtk.soDinh; i++) {
		if (mtk.maTranKe[i][u] != 0)
			count++;
	}
	return count;
}

void Topo(maTrix graph, vector<int>& topo) {
	// Khởi tạo mảng banBac và tính bậc vào của các đỉnh
	int banBac[MAX] = { 0 };
	for (int i = 0; i < graph.soDinh; i++) {
		banBac[i] = tinhBacVao(graph, i);
	}

	queue<int> hangDoi;
	for (int i = 0; i < graph.soDinh; i++) {
		if (banBac[i] == 0) {
			hangDoi.push(i);
		}
	}

	// Duyệt qua các đỉnh trong hàng đợi
	while (!hangDoi.empty()) {
		int dinhHienTai = hangDoi.front();
		hangDoi.pop();
		topo.push_back(dinhHienTai);

		// Duyệt qua các đỉnh kề của đỉnh hiện tại
		for (int i = 0; i < graph.soDinh; i++) {
			if (graph.maTranKe[dinhHienTai][i] != 0) {
				int dinhKe = i;
				banBac[dinhKe]--;
				if (banBac[dinhKe] == 0) {
					hangDoi.push(dinhKe);
				}
			}
		}
	}
}

int main() {
	maTrix graph;
	readFile(graph);

	vector<int> topo; 
	Topo(graph, topo); 

	// In ra thứ tự topological 
	for (int x : topo)
		cout << x << " ";

	return 0;
}