/*THÔNG TIN*********************************************************************
 *Tập tin		: vertex_cover.h
 *Mô tả			: Tìm phủ đỉnh
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//______________________________________________________________________________
// Khởi tạo thuật toán tìm lớp phủ đỉnh kích thước không lớn hơn k
void graph :: Initiate_cover()	{
	wgt_to_adj_lst();
	Initiate_result(0);

	cout << "Thuc hien thuat toan tim kiem lop phu dinh..........";
	start_time = clock();
}

// Tìm lớp phủ đỉnh kích thước không lớn hơn k-1
bool graph :: Vertex_cover(vector <vector <uint16_t> > temp, uint16_t not, uint16_t ver)	{
	// Loại đỉnh not và các đỉnh lân cận của nó
	if (not != UINT16_MAX)	{
		temp[not].clear();

		for (uint16_t i=0; i<temp.size(); i++)
			for (uint16_t j=0; j<temp[i].size(); j++)
				if (temp[i][j] == not)
					temp[i].erase(temp[i].begin() + j);
	}

	// Đếm số cạnh hiện tại
	uint16_t counter = 0;
	
	for (uint16_t i=0; i<temp.size(); i++)
		counter = counter + temp[i].size();

	// Bắt đầu thuật toán
	if (!counter)
		return true;
	else if (counter > k * ver)
		return false;
	else	{
		uint16_t i;

		for (i=0; i!=temp.size(); ++i)
			// Kiểm tra xem từ i có cạnh nào không
			for (uint16_t k = 0; k!=temp[i].size(); ++k)	{
				if (Vertex_cover(temp, i, ver-1))	{
					result.push_back(i);
					return true;
				}
				else	{
					uint16_t j;

					for (j=0; j!=temp[i].size(); ++j)
						if (Vertex_cover(temp, temp[i][j], ver-1))	{
							result.push_back(temp[i][j]);
								return true;
						}
			
					if (j == temp[i].size())
						return false;
				}

				break;
			}

		if (i == temp.size())
			return false;
	}
}

// In kết quả tìm kiếm lớp phủ đỉnh ra file .out
void graph :: Print_cover_to_out(string input_header)	{
	fstream f = New_output_file(input_header, "_Cover", ".out");

	// Bắt đầu lưu kết quả
	if (result.size() > k || result.size() == 0)	{
			f << "Do thi vua nhap khong co phu dinh kich thuoc khong lon hon " << k << "." << endl;
			cout << "Xong." << endl;
			f.close();
			return;
		}

	f << "Cac dinh trong Phu dinh kich thuoc khong lon hon " << k << " la: " << endl;

	for (uint16_t i=0; i!=result.size(); ++i)
		f << result[i] + 1 << " ";

	f << endl;
	f.close();
	cout << "Xong." << endl;
}

// In kết quả tìm kiếm lớp phủ đỉnh ra file .dot
void graph :: Print_cover_to_dot(string input_header)	{
	fstream f = New_output_file(input_header, "_Cover", ".dot");

	// Bắt đầu lưu
	if (directed)
		f << "digraph " << input_header << "_Cover {" << endl;
	else
		f << "graph " << input_header << "_Cover {" << endl;

	if (result.size() > k || result.size() == 0)	{
		f << "label = \"\\n\\nDo thi nhap tu file khong co phu dinh kich thuoc khong lon hon " << k << ".\"\n}";
	}
	else	{
		// Các đỉnh nằm trong tập kết quả được tô màu đỏ
		f << "node [style = filled, color = red]";
		for (uint16_t i=0; i!=result.size(); ++i)
			f << " " << result[i]+1;
		f << endl;

		// Các đỉnh còn lại tô màu xanh
		f << "node [style = filled, color = green]";
		vector <uint16_t> b(vertices);

		for (uint16_t i=0; i!=vertices; ++i)
			b[i] = i+1;

		for (uint16_t i=0; i!=result.size(); ++i)
			b[result[i]] = UINT16_MAX;

		for (uint16_t i=0; i!=vertices; ++i)
			if (b[i] != UINT16_MAX)
				f << " " << b[i];
		f << endl;

		for (uint16_t i=0; i<vertices; ++i)
			for (uint16_t j=0; j<vertices; ++j)
				if (Has_edge_wgt(i, j))	{
					if (!directed && i>j)
						continue;

					if (directed)
						f << i+1 << " -> " << j+1;
					else
						f << i+1 << " -- " << j+1;

					if (weighted)
						f << " [label = \"" << wgt[i][j] << "\"]" << endl;
					else
						f << endl;
				}

		f << "label = \"\\n\\nPhu dinh kich thuoc khong lon hon " << k 
		  << "\\ncua do thi voi du lieu tu file\"\n}";
	}
	
	f.close();
	cout << "Xong." << endl;
}

// Tìm phủ đỉnh và hiển thị kết quả
void graph :: Find_vertex_cover(string output_header, output_type type, ver_t max_size)	{
	k = max_size;
	Initiate_cover();
	bool ok = Vertex_cover(adj_lst, UINT16_MAX, vertices);
	Print_runtime();

	if (type == OUT)
		Print_cover_to_out(output_header);
	else if (type == DOT)
		Print_cover_to_dot(output_header);
	else	{
		Print_cover_to_dot(output_header);
		Dot_to_bmp(output_header, "_Cover");
	}
}
