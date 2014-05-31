/*THÔNG TIN*********************************************************************
 *Tập tin		: traverse.h
 *Mô tả			: Các phương thức duyệt đồ thị
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//______________________________________________________________________________
// Khởi tạo cho thuật toán duyệt
void graph :: Initiate_traverse()	{
	Initiate_final(vertices);
	Initiate_result(0);

	cout << "Thuc hien thuat toan duyet..........";
	start_time = clock();
}

// Duyệt theo chiều rộng
void graph :: BFS(ver_t start)	{
	// Khởi tạo
	vector <ver_t> queue (vertices, UINT16_MAX);
	queue[0] = start;
	final[start] = true;
	ver_t i, left = 0, right = 0;

	while (left <= right)	{
		i = queue[ left++ ];
		result.push_back(i);

		for (ver_t j=0; j!=vertices; ++j)
			if ( Has_edge_wgt(i, j) && !final[j] )	{
				queue[ ++right ] = j;
				final[j] = true;
			}
	}
}

// Duyệt theo chiều sâu
void graph :: DFS(ver_t ver)	{
	final[ver] = true;
	result.push_back(ver);

	for (ver_t i=0; i!=vertices; ++i)
		if (Has_edge_wgt(ver, i) && !final[i])
			DFS(i);
}

// In kết quả duyệt ra file
void graph :: Print_traverse_to_out(string input_header, string opt)	{
	fstream f = New_output_file(input_header, opt, ".out");

	// Bắt đầu lưu file
	f << "Thu tu duyet cac dinh la: " << endl;

	for (uint16_t i=0; i!=result.size(); ++i)
		f << result[i]+1 << " ";

	f << endl;

	cout << "Xong." << endl;
	f.close();
}

// In đồ thị với thứ tự duyệt các đỉnh
void graph :: Print_traverse_to_dot(string input_header, string opt)	{
	fstream f = New_output_file(input_header, opt, ".dot");

	// Bắt đầu lưu file
	if (directed)
		f << "digraph " << input_header << opt << " {" << endl;
	else
		f << "graph " << input_header << opt << " {" << endl;

	for (uint16_t i=0; i!=vertices; ++i)
		for (uint16_t j=0; j!=vertices; ++j)	{
			if (Has_edge_wgt(i, j))	{
				if (!directed && i>j)
					continue;

				f << i+1;

				for (uint16_t k = 0; k!=result.size(); ++k)
					if (result[k] == i)	{
						f << "." << k+1;
						break;
					}

				if (directed)
					f << " -> " << j+1;
				else
					f << " -- " << j+1;

				for (uint16_t k = 0; k!=result.size(); ++k)
					if (result[k] == j)	{
						f << "." << k+1;
						break;
					}

				if (weighted)
					f << " [label = \"" << wgt[i][j] << "\"]" << endl;
				else
					f << endl;
			}
		}

	string alg(opt.begin() + 1, opt.end());
	f << "label = \"\\n\\nThu tu duyet do thi theo thuat toan "
	  << alg << "\\nvoi du lieu tu file\"\n}";

	f.close();
	cout << "Xong." << endl;
}

// Duyệt đồ thị và hiển thị kết quả
void graph :: Traverse(traverse_algol alg, string output_header, output_type type)	{
	Initiate_traverse();

	string opt;
	if (alg == DFS_ALG)	{
		DFS(0);
		opt = "_DFS";
	}
	else if (alg == BFS_ALG)	{
		BFS(0);
		opt = "_BFS";
	}

	Print_runtime();

	if (type == OUT)
		Print_traverse_to_out(output_header, opt);
	else if (type == DOT)
		Print_traverse_to_dot(output_header, opt);
	else	{
		Print_traverse_to_dot(output_header, opt);
		Dot_to_bmp(output_header, opt);
	}
}