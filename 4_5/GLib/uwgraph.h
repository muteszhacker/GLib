/*THÔNG TIN*********************************************************************
 *Tập tin		: uwgraph.h
 *Mô tả			: Thư viện đồ thị vô hướng, có trọng số
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//______________________LỚP ĐỒ THỊ VÔ HƯỚNG, KHÔNG TRỌNG SỐ_____________________
class uwgraph : public ugraph	{
public:
	//__________________THUỘC TÍNH DÙNG KHI CHẠY THUẬT TOÁN_____________________

	// Tổng trọng số cây khung nhỏ nhất
	double sum_length;
	// Mảng lưu các cạnh của cây khung nhỏ nhất
	vector <w_edge> SpanTree_edge;

	//__________________________PHƯƠNG THỨC KHỞI TẠO____________________________

	// Phương thức khởi tạo mặc định
	uwgraph();
	// Khởi tạo đồ thị với số đỉnh xác định
	uwgraph(ver_t ver);
	// Khởi tạo đồ thị nhập từ file
	uwgraph(input_type type, string input_header);
	// Khởi tạo đồ thị từ một ma trận đã có
	uwgraph(vector < vector <wgt_t> > mtr);

	//_________________________________PRIM_____________________________________
	// Khởi tạo cho thuật toán Prim
	void Initiate_prim();
	// Thuật toán Prim tìm cây khung nhỏ nhất
	void Prim();
	// In kết quả cây khung tìm được ra file .out
	void Print_sptr_to_out(string input_header, string opt);
	// In kết quả cây khung tìm được ra file .dot
	void Print_sptr_to_dot(string input_header, string opt);
	// Tìm cây khung nhỏ nhất và hiển thị kết quả
	void Find_min_span_tree(min_span_tree_alg alg, string output_header, output_type type);
};/*Kết thúc khai báo lớp uwgraph*/

//______________________________________________________________________________
// Phương thức khởi tạo mặc định
uwgraph :: uwgraph()	{
	weighted = true;
}

// Khởi tạo đồ thị với số đỉnh xác định
uwgraph :: uwgraph(ver_t ver)	{
	vertices = ver;
	weighted = true;
	Initiate_wgt(ver);
}

// Khởi tạo đồ thị từ file
uwgraph :: uwgraph(input_type type, string input_header)	{
	weighted = true;

	if (type == W_TXT)
		Read_txt(type, input_header);
	else if (type == GRF)
		Read_grf(input_header);

	for (auto i=0; i<wgt.size(); ++i)
		for (auto j=0; j<wgt[i].size(); ++j)
			if (Has_edge_wgt(i, j))
				wgt[j][i] = wgt[i][j];
}

// Khởi tạo đồ thị từ một ma trận đã có
uwgraph :: uwgraph(vector < vector <wgt_t> > mtr)	{
	weighted = true;

	Initiate_wgt(vertices);

	for (auto i=0; i<vertices; ++i)
		for (auto j=0; j<vertices; ++j)	{
			if (mtr[i][j] != UINT16_MAX)
				++edges;
			wgt[i][j] = mtr[i][j];
		}
}

//______________________________________________________________________________
// Khởi tạo cho thuật toán Prim
void uwgraph :: Initiate_prim()	{
	sum_length = 0.0;
	SpanTree_edge.clear();

	cout << "Thuc hien thuat toan tim cay khung nho nhat..........";
	start_time = clock();
}

// Thuật toán Prim tìm cây khung nhỏ nhất
void uwgraph :: Prim()	{
	Initiate_final(vertices);
	final[0] = true;

	do	{
		double min = UINT16_MAX;
		uint16_t last_i = UINT16_MAX, last_j = UINT16_MAX;

		for (uint16_t i=0; i!=vertices; ++i)
			for (uint16_t j=0; j!=vertices; ++j)
				if (i<j && wgt[i][j]<min && final[i] && !final[j])	{
					min = wgt[i][j];
					last_i = i;
					last_j = j;
				}

				if (last_j == UINT16_MAX)
					return;

				final[last_j] = true;

				w_edge e;
				e.start = last_i;
				e.finish = last_j;
				e.weight = wgt[last_i][last_j];
				SpanTree_edge.push_back(e);

				sum_length += wgt[last_i][last_j];
	} while (SpanTree_edge.size() != vertices - 1);

	final.clear();
}

// In kết quả cây khung tìm được ra file .out
void uwgraph :: Print_sptr_to_out(string input_header, string opt)	{
	fstream f = New_output_file(input_header, opt, ".out");

	// Bắt đầu lưu kết quả
	f << "Cac canh cua cay khung la:" << endl;
	
	for (uint16_t i=0; i!=SpanTree_edge.size(); ++i)
		f << SpanTree_edge[i].start+1 << ", " << SpanTree_edge[i].finish+1 << ", " << SpanTree_edge[i].weight << endl;

	f << "Tong trong so cay khung la " << sum_length << endl;

	f.close();
	cout << "Xong." << endl;
}

// In kết quả cây khung tìm được ra file .dot
void uwgraph :: Print_sptr_to_dot(string input_header, string opt)	{
	fstream f = New_output_file(input_header, opt, ".dot");

	f << "graph " << input_header << opt << " {" << endl;

	for (uint16_t i=0; i<vertices; ++i)
		for (uint16_t j=0; j<vertices; ++j)	{
			if (i<j && Has_edge_wgt(i, j))	{
				f << i+1 << " -- " << j+1 << " [";

				uint16_t k;

				for (k=0; k!=SpanTree_edge.size(); ++k)
					if (SpanTree_edge[k].start == i && SpanTree_edge[k].finish == j)
						break;

				if (k == SpanTree_edge.size())
					f << "style = dotted, ";

				f << "label = \"" << wgt[i][j] << "\"]" << endl;
			}
		}

		f << "label = \"\\n\\nCay khung nho nhat co do dai " << sum_length << " cua do thi\\n"
		  << "dung thuat toan Prim voi du lieu tu file\"\n}";

	f.close();
	cout << "Xong." << endl;
}

// Tìm cây khung nhỏ nhất và hiển thị kết quả
void uwgraph :: Find_min_span_tree(min_span_tree_alg alg, string output_header, output_type type)	{
	string opt;
	if (alg == PRIM)	{
		Initiate_prim();
		Prim();
		Print_runtime();
		opt = "_Prim";
	}

	if (type == OUT)
		Print_sptr_to_out(output_header, opt);
	else if (type == DOT)
		Print_sptr_to_dot(output_header, opt);
	else	{
		Print_sptr_to_dot(output_header, opt);
		Dot_to_bmp(output_header, opt);
	}
}