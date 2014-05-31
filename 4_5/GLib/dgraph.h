/*THÔNG TIN*********************************************************************
 *Tập tin		: dgraph.h
 *Mô tả			: Thư viện đồ thị có hướng
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//___________________________LỚP ĐỒ THỊ CÓ HƯỚNG________________________________
class dgraph : public graph	{
public:
	//__________________________PHƯƠNG THỨC KHỞI TẠO____________________________

	// Phương thức khởi tạo mặc định
	dgraph();

	//____________________________SẮP XẾP TOPO__________________________________

	// Khởi tạo cho thuật toán Topo
	void Initiate_topo();
	// Tính bậc của các đỉnh
	void Calc_deg(vector <uint16_t> &deg);
	// Thuật toán Topo đánh số lại các đỉnh
	void Topological_order();
	// In kết quả đánh số ra file .out
	void Print_topo_to_out(string input_header);
	// In kết quả đánh số ra file .dot
	void Print_topo_to_dot(string input_header);
	// Sắp xếp Topo và hiển thị kết quả
	void Topo(string output_header, output_type type);
};

//______________________________________________________________________________
/*Phương thức khởi tạo mặc định*/
dgraph :: dgraph()	{
	directed = true;
}

//______________________________________________________________________________
// Phương thức khởi tạo mặc định
void dgraph :: Initiate_topo()	{
	Initiate_result(vertices);
	fill(result.begin(), result.end(), UINT16_MAX);

	cout << "Thuc hien thuat toan Topo..........";
	start_time = clock();
}

// Tính bán bậc vào của các đỉnh
void dgraph :: Calc_deg(vector <uint16_t> &deg)	{
	for (uint16_t i=0; i!=vertices; ++i)
		for (uint16_t j=0; j!=vertices; ++j)
			if (Has_edge_wgt(i, j))
				++deg[j];
}

// Thuật toán Topo đánh số lại các đỉnh
void dgraph :: Topological_order()	{
	vector <uint16_t> deg(vertices);
	Calc_deg(deg);

	// Khởi tạo queue, cho các đỉnh có bậc = 0 vào hàng đợi queue
	vector <uint16_t> queue(vertices, UINT16_MAX);
	uint16_t i, left = 0, right = 0, num = 0;

	for (i=0; i!=vertices; ++i)
		if (deg[i] == 0)
			queue[right++] = i;

	// Đánh số lại đỉnh
	while (left < right)	{
		i = queue[ left++ ];
		result[i] = (num++);

		for (uint16_t j=0; j!=vertices; ++j)
			if (Has_edge_wgt(i, j))	{
				--deg[j];

				if (deg[j] == 0)
					queue[ right++ ] = j;
			}
	}

	Print_runtime();
}

// In kết quả đánh số ra file .out
void dgraph :: Print_topo_to_out(string input_header)	{
	fstream f = New_output_file(input_header, "_Topo", ".out");

	// Kiểm tra nếu đồ thị có chu trình
	for (uint16_t i=0; i!=vertices; ++i)
		if (result[i] == UINT16_MAX)	{
			f << "Do thi vua nhap co chu trinh." << endl;
			cout << "Xong.\n";
			f.close();
			return;
		}

	// In thứ tự đỉnh mới ra file
	f << "Thu tu cac dinh moi la: " << endl;

	for (uint16_t i=0; i!=result.size(); ++i)
		f << result[i]+1 << " ";
	
	f << endl;
	f.close();
	cout << "Xong.\n";
}

// In kết quả đánh số ra file .dot
void dgraph :: Print_topo_to_dot(string input_header)	{
	fstream f = New_output_file(input_header, "_Topo", ".dot");

	// Bắt đầu lưu đồ thị ra file .dot
	f << "digraph " << input_header << "_Topo {" << endl;

	uint16_t k;

	for (k=0; k!=vertices; ++k)
		if (result[k] == UINT16_MAX)	{
			f << "label = \"\\n\\nDo thi nhap tu file co chu trinh.\"\n}";
			break;
		}

	if (k == vertices)	{
		for (uint16_t i=0; i<vertices; ++i)
			for (uint16_t j=0; j<vertices; ++j)
				if (Has_edge_wgt(i, j))	{
					f << i+1 << "." << result[i]+1 << " -> " << j+1 << "." << result[j]+1;

					if (weighted)
						f << " [label = \"" << wgt[i][j] << "\"]" << endl;
					else
						f << endl;
				}

		f << "label = \"\\n\\nDo thi duoc danh so lai nho thuat toan Topo\\nvoi du lieu tu file.\"\n}";
	}

	f.close();
	cout << "Xong." << endl;
}

// Sắp xếp topo và hiển thị kết quả
void dgraph :: Topo(string output_header, output_type type)	{
	Initiate_topo();
	Topological_order();
	Print_runtime();

	if (type == OUT)
		Print_topo_to_out(output_header);
	else if (type == DOT)
		Print_topo_to_dot(output_header);
	else	{
		Print_topo_to_dot(output_header);
		Dot_to_bmp(output_header, "_Topo");
	}
}