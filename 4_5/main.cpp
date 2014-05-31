/*THÔNG TIN*********************************************************************
 *Tập tin		: main.cpp
 *Mô tả			: Chương trình minh họa các thuật toán với đồ thị
 *Ngày tạo		: 29/08/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

#include "GLib.h"

void Option();
void Control();

/*Chương trình chính*/
int main()	{
	Control();

	cin.ignore();
	return 0;
}/*Kết thúc hàm main*/

/*In ra các tùy chọn phím điều khiển*******************************************/
void Option()	{
	cout <<"Chuong trinh minh hoa cac thao tac voi do thi\n\n";
	cout << "Nhan phim :\n\n";
	cout << "a. Kiem tra canh\n";
	cout << "b. Them canh\n";
	cout << "c. Xoa canh\n";
	cout << "d. In cac canh\n";
	cout << "e. In cac dinh\n";
	cout << "f. Xuat ra hinh anh\n";
	cout << "g. Duyet do thi\n";
//	cout << "h. Sap xep topo\n";
//	cout << "h. Tim cay khung nho nhat\n";
//	cout << "h. Tim duong di ngan nhat\n";
	cout << "h. Tim phu dinh\n";
	cout << "i. Tim tap doc lap\n";
	cout << "0. Thoat\n\n";
}/*Kết thúc hàm Option*********************************************************/

/*Điều khiển chương trình từ bàn phím******************************************/
void Control()	{
	char ch;
	bool kt = true;
//	dwgraph g(10);

	string input_header;
	cout << "Nhap tieu de (header) file: ";
	cin >> input_header;

	uugraph g(GRF, input_header);

	ver_t start, finish;

	Option();

	while (kt)	{
		cout << "\nChon 1 chuc nang: ";
		fflush(stdin);
		cin >> ch;
	
		switch (ch)	{
			case 'a':	cout << "Nhap canh can kiem tra: \n";
						cout << "Dinh dau: ";
						cin >> start;
						cout << "Dinh cuoi: ";
						cin >> finish;

						if (g.Has_edge(start, finish))
							cout << "Canh (" << start << ", " << finish << ") da co trong do thi" << endl;
						else 
							cout << "Canh (" << start << ", " << finish << ") khong co trong do thi" << endl;
						break;
			case 'b':	cout << "Nhap canh muon them: \n";
						cout << "Dinh dau: ";
						cin >> start;
						cout << "Dinh cuoi: ";
						cin >> finish;

						if (g.Add_edge(start, finish))
							cout << "Canh (" << start << ", " << finish << ") da duoc them vao do thi" << endl;
						else
							cout << "Khong the them canh nay" << endl;
						break;
			case 'c':	cout << "Nhap canh muon xoa: \n";
						cout << "Dinh dau: ";
						cin >> start;
						cout << "Dinh cuoi: ";
						cin >> finish;

						if (g.Remove_edge(start, finish))
							cout << "Canh (" << start << ", " << finish << ") da duoc xoa khoi do thi" << endl;
						else
							cout << "Khong the xoa canh nay" << endl;
						break;
			case 'd':	g.Print_edges();
						break;
			case 'e':	g.Print_vertices();
						break;
			case 'f':	g.Export_graph(input_header, BMP);
						break;
			case 'g':	g.Traverse(DFS_ALG, input_header, BMP);
						break;
//			case 'h':	g.Topo(input_header, BMP);
//						break;
//			case 'h':	g.Find_min_span_tree(PRIM, input_header, BMP);
//						break;
//			case 'h':	g.Find_shortest_path(DIJKSTRA, input_header, BMP, 4, 3);
//						break;
//			case 'h':	g.Find_vertex_cover(input_header, BMP, 13);
//						break;
			case 'i':	g.Find_max_indep_set(MAX_SIZE, input_header, BMP);
						break;
			case '0':	kt=false;
						cout << "Ket thuc...\n";
						break;
			default:	cout << "Chon sai, moi chon lai\n";
		}
	}
}/*Kết thúc hàm Control********************************************************/

/*Kết thúc chương trình*/