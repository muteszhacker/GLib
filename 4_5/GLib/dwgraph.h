/*THÔNG TIN*********************************************************************
 *Tập tin		: dwgraph.h
 *Mô tả			: Thư viện đồ thị có hướng, có trọng số
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//______________________LỚP ĐỒ THỊ CÓ HƯỚNG, CÓ TRỌNG SỐ_______________________
class dwgraph : public dgraph	{
public:
	//__________________THUỘC TÍNH DÙNG KHI CHẠY THUẬT TOÁN_____________________

	ver_t source;				// Đỉnh xuất phát
	ver_t target;				// Đỉnh đích
	vector <uint16_t> before;	// Mảng lưu đỉnh trước trong khi duyệt
	vector <double> min_len;	// Mảng lưu độ dài đường đi từ source đến đỉnh i

	//__________________________PHƯƠNG THỨC KHỞI TẠO____________________________

	// Phương thức khởi tạo mặc định
	dwgraph();
	// Khởi tạo đồ thị với số đỉnh xác định
	dwgraph(ver_t ver);
	// Khởi tạo đồ thị nhập từ file
	dwgraph(input_type type, string input_header);
	// Khởi tạo đồ thị từ một ma trận đã có
	dwgraph(vector < vector <wgt_t> > mtr);

	//_________________________________DIJKSTRA_________________________________

	// Khởi tạo cho thuật toán Dijkstra
	void Initiate_dijkstra();
	// Thuật toán Dijkstra tìm đường đi ngắn nhất
	void Dijkstra();
	// Lưu đường đi vào mảng result
	void Build_result();
	// In kết quả tìm đường đi ngắn nhất ra file .out
	void Print_path_to_out(string input_header, string opt);
	// In kết quả tìm đường đi ngắn nhất ra file .dot
	void Print_path_to_dot(string input_header, string opt);
	// Tìm đường đi ngắn nhất và hiển thị kết quả
	void Find_shortest_path(shortest_path_alg alg, string output_header, output_type type, ver_t s, ver_t t);
};

//______________________________________________________________________________
// Phương thức khởi tạo mặc định
dwgraph :: dwgraph()	{
	weighted = true;
}

// Khởi tạo đồ thị với số đỉnh xác định
dwgraph :: dwgraph(ver_t ver)	{
	vertices = ver;
	weighted = true;
	Initiate_wgt(ver);
}

// Khởi tạo đồ thị nhập từ file
dwgraph :: dwgraph(input_type type, string input_header)	{
	weighted = true;

	if (type == W_TXT)
		Read_txt(type, input_header);
	else if (type == GRF)
		Read_grf(input_header);
}

// Khởi tạo đồ thị từ một ma trận đã có
dwgraph :: dwgraph(vector < vector <wgt_t> > mtr)	{
	weighted = true;
	Initiate_wgt(vertices);

	for (auto i=0; i<vertices; ++i)
		for (auto j=0; j<vertices; ++j)	{
			if (mtr[i][j] != UINT16_MAX)
				++edges;
			wgt[i][j] = mtr[i][j];
		}
}

// Khởi tạo cho thuật toán Dijkstra
void dwgraph :: Initiate_dijkstra()	{
	// Khởi tạo các mảng final, before, min_len
	Initiate_final(vertices);
	final[source] = true;

	before.resize(vertices);
	fill(before.begin(), before.end(), source);
	before[source] = UINT16_MAX;

	min_len.resize(vertices);
	for (uint16_t i=0; i<vertices; ++i)
		min_len[i] = wgt[source][i];
	
	Initiate_result(0);

	cout << "Thuc hien thuat toan Dijkstra..........";
	start_time = clock();
}

// Thuật toán Dijkstra tìm đường đi ngắn nhất
void dwgraph :: Dijkstra()	{
	uint16_t i, j;

	do	{
		double min = double(UINT16_MAX);
		i = UINT16_MAX;

		/*Tìm trong các đỉnh lân cận j đỉnh nào gần đỉnh bắt đầu nhất*/
		for (j=0; j<vertices; ++j)	{
			if (!final[j])
				if (min>min_len[j])	{
					min = min_len[j];
					i = j;
			}
		}

		// Kết thúc khi không tìm được đỉnh j nào hoặc đã tìm được đến đích
		if (i==UINT16_MAX || i==target)
			break;

		// Đánh dấu đỉnh i đã xét xong
		final[i] = true;

		// Tối ưu đường đi và lưu vết đường đi
		for (j=0; j<vertices; ++j)
			if (!final[j])
				if (min_len[j] > min_len[i] + wgt[i][j])	{
					min_len[j] = min_len[i] + wgt[i][j];
					before[j] = i;
			}
	} while (true);
}

/*Lưu đường đi vào mảng result*/
void dwgraph :: Build_result()	{
	if (min_len[target] != UINT16_MAX)	{
		result.push_back(target);

		uint16_t i = target;

		while (before[i] != UINT16_MAX)	{
			i = before[i];
			result.push_back(i);
		}
	}
}

// In kết quả tìm đường đi ngắn nhất ra file .out
void dwgraph :: Print_path_to_out(string input_header, string opt)	{
	fstream f = New_output_file(input_header, opt, ".out");

	if (min_len[target] == UINT16_MAX)
		f << "Khong co duong di tu " << source+1 << " den " 
		  << target+1 << "." << endl;
	else	{
		f << "Do dai duong di ngan nhat tu " << source+1 << " den " 
		  << target+1 << " la " << min_len[target] << "." << endl
		  << "Duong di la: " << endl;

		for (uint16_t i=result.size()-1; i!=0; --i)
			f << result[i]+1 << "--(" << wgt[result[i]][result[i-1]] << ")-->";

		f << result[0] + 1 << endl;
	}

	f.close();
	cout << "Xong." << endl;
}

// In kết quả tìm đường đi ngắn nhất ra file .dot
void dwgraph :: Print_path_to_dot(string input_header, string opt)	{
	fstream f = New_output_file(input_header, opt, ".dot");

	f << "digraph " << input_header << opt << " {" << endl;

	if (min_len[target] == UINT16_MAX)	{
		f << "label = \"\\n\\nKhong co duong di tu " << source + 1 << " den " 
		  << target + 1 << " voi du lieu tu file.\"\n}";
	}
	else	{
		for (uint16_t i=0; i<vertices; ++i)
			for (uint16_t j=0; j<vertices; ++j)	{
				if (wgt[i][j] != UINT16_MAX)	{
					f << i+1 << " -> " << j+1 << " [";

					uint16_t k;

					for (k=result.size()-1; k!=0; --k)
						if (result[k] == i && result[k-1] == j)
							break;

					if (k == 0)
						f << "style = dotted, ";

					f << "label = \"" << wgt[i][j] << "\"]" << endl;
				}
			}

		f << "label = \"\\n\\nDuong di ngan nhat dung thuat toan "
		  << "Dijkstra voi du lieu tu file\\n"
		  << "Do dai duong di ngan nhat tu " << source + 1 << " den " 
		  << target+1 << " la " << min_len[target] << ".\"\n}";
	}	

	f.close();
	cout << "Xong." << endl;
}

// Tìm đường đi ngắn nhất và hiển thị kết quả
void dwgraph :: Find_shortest_path(shortest_path_alg alg, string output_header, output_type type, ver_t s, ver_t t)	{
	source = s-1;
	target = t-1;

	string opt;
	if (alg == DIJKSTRA)	{
		Initiate_dijkstra();
		Dijkstra();
		Build_result();
		Print_runtime();
		opt = "_Dijkstra";
	}

	if (type == OUT)
		Print_path_to_out(output_header, opt);
	else if (type == DOT)
		Print_path_to_dot(output_header, opt);
	else	{
		Print_path_to_dot(output_header, opt);
		Dot_to_bmp(output_header, opt);
	}
}