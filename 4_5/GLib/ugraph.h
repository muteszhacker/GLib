/*THÔNG TIN*********************************************************************
 *Tập tin		: ugraph.h
 *Mô tả			: Thư viện đồ thị vô hướng
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//___________________________LỚP ĐỒ THỊ VÔ HƯỚNG________________________________
class ugraph : public graph	{
public:
	//__________________THUỘC TÍNH DÙNG KHI CHẠY THUẬT TOÁN_____________________

	// Kích thước rừng đang duyệt
	uint16_t size;
	// Trọng số cực đại của tập độc lập của cây con T_u chứa u
	vector <double> max_in;
	// Trọng số cực đại của tập độc lập của cây con T_u không chứa u
	vector <double> max_out;
	// Mảng lưu giá trị max(max_in[i], max_out[i])
	vector <double> big;
	// Trọng số ứng với mỗi đỉnh v - là trọng số cạnh (v, i) lớn nhất
	vector <double> weight;

	//__________________________PHƯƠNG THỨC KHỞI TẠO____________________________

	// Phương thức khởi tạo mặc định
	ugraph();

	//__________________________TÌM TẬP ĐỘC LẬP CỰC ĐẠI_________________________

	// Khởi tạo thuật toán tìm tập độc lập kích thước lớn nhất
	void Initiate_indep_set();

	//____________________TÌM TẬP ĐỘC LẬP CỰC ĐẠI VỀ SỐ ĐỈNH____________________

	// Tìm cạnh (u, v) có v là lá
	edge Find_edge_of_leaf();
	// Thuật toán tìm tập độc lập kích thước lớn nhất với đồ thị cây/rừng
	void Find_max_size_indep_set();
	// In kết quả tìm kiếm tập độc lập kích thước lớn nhất ra file .out
	void Print_max_size_indep_set_to_out(string input_header);
	// In kết quả tìm kiếm tập độc lập kích thước lớn nhất ra file .dot
	void Print_max_size_indep_set_to_dot(string input_header);

	//__________________TÌM TẬP ĐỘC LẬP CỰC ĐẠI VỀ TRỌNG SỐ_____________________

	// Tính big(v) tại v
	void Calculate_big(uint16_t v);
	// Duyệt cây theo thứ tự sau
	void Max_tree(uint16_t v);
	// Tìm tập độc lập có trọng số lớn nhất với đồ thị cây/rừng
	void Find_max_weight_indep_set();
	// Xây dựng mảng kết quả result
	void Build_result();
	// In kết quả tìm kiếm tập độc lập có trọng số lớn nhất ra file .out
	void Print_max_weight_indep_set_to_out(string input_header);
	// In kết quả tìm kiếm tập độc lập có trọng số lớn nhất ra file .dot
	void Print_max_weight_indep_set_to_dot(string input_header);
	// Tìm tập độc lập cực đại về kích thước hoặc trọng số và hiển thị kết quả
	void Find_max_indep_set(max_indep_alg alg, string output_file, output_type type);
};

//______________________________________________________________________________
// Phương thức khởi tạo mặc định
ugraph :: ugraph()	{
	directed = false;
}

//______________________________________________________________________________
// Khởi tạo thuật toán tìm tập độc lập kích thước lớn nhất
void ugraph :: Initiate_indep_set()	{
	Initiate_result(0);	
	cout << "Thuc hien thuat toan tim kiem tap doc lap..........";
	start_time = clock();
}

//______________________________________________________________________________
// Tìm cạnh (u, v) có v là lá
edge ugraph :: Find_edge_of_leaf()	{
	edge e;
	e.start = e.finish = UINT16_MAX;

	for (uint16_t i=0; i!=adj_lst.size(); ++i)	{
		for (uint16_t j=0; j!=adj_lst[i].size(); ++j)	{
			e.finish = adj_lst[i][j];

			if (adj_lst[e.finish].size() == 1)	{
				e.start = i;

				result.push_back(e.finish);
				final[e.finish] = true;

				return e;
			}
		}
	}

	return e;
}

// Thuật toán tìm tập độc lập có trọng số lớn nhất với đồ thị cây/rừng
void ugraph :: Find_max_size_indep_set()	{
	edges = edges * 2;
	size = edges;
	wgt_to_adj_lst(true);

	final.resize(vertices);

	while (size)	{
		edge e = Find_edge_of_leaf();

		// Nếu tìm được cạnh
		if (e.start != UINT16_MAX)	{
			// Kiểm tra v có phải là lá duy nhất
			bool only_leaf = true;
			uint16_t u = e.start, v = e.finish;

			for (uint16_t i=0; i!=adj_lst[u].size(); ++i)	{
				uint16_t leaf = adj_lst[u][i];

				if (leaf!=v && adj_lst[leaf].size()==1)	{
					only_leaf = false;
					break;
				}
			}

			// Nếu là lá duy nhất thì xóa hết tất cả các con của u
			if (only_leaf)	{
				size -= adj_lst[u].size();
				adj_lst[u].clear();
				final[u] = true;

				// Xóa các cạnh nối đến u
				for (uint16_t k=0; k<adj_lst.size(); ++k)
					for (uint16_t t=0; t<adj_lst[k].size(); ++t)
						if (adj_lst[k][t] == u)	{
							adj_lst[k].erase(adj_lst[k].begin()+t);

							--size;
						}

			}
			// Còn không là lá duy nhất thì chỉ xóa nó thôi
			else	{
				adj_lst[v].clear();
				--size;

				for (uint16_t i=0; i!=adj_lst[u].size(); ++i)
					if (adj_lst[u][i] == v)	{
						adj_lst[u].erase(adj_lst[u].begin() + i);
						--size;
						break;
					}
			}
		}
		else
			break;
	}

	// Nếu còn đỉnh nào chưa xét mà nằm trơ không có cạnh nào liên quan thì thêm nó vào result
	for (uint16_t i=0; i!=adj_lst.size(); ++i)
		if (adj_lst[i].size() == 0 && !final[i])	{
			result.push_back(i);
			final[i] = true;
		}

	final.clear();
	edges = edges / 2;
}

// In kết quả tìm kiếm tập độc lập kích thước lớn nhất ra file .out
void ugraph :: Print_max_size_indep_set_to_out(string input_header)	{
	fstream f = New_output_file(input_header, "_Max_size_indep", ".out");

	// Bắt đầu in kết quả ra file
	if (size)
			f << "Do thi da cho khong phai la rung." << endl;
	else	{
		f << "Cac dinh trong tap doc lap lon nhat la: " << endl;

		for (uint16_t i=0; i!=result.size(); ++i)
			f << result[i] + 1 << " ";

		f << endl;
	}

	f.close();
	cout << "Xong." << endl;
}

// In kết quả tìm kiếm tập độc lập kích thước lớn nhất ra file .dot
void ugraph :: Print_max_size_indep_set_to_dot(string input_header)	{
	fstream f = New_output_file(input_header, "_Max_size_indep", ".dot");

	// Bắt đầu in file
	f << "graph " << input_header << "_Max_size_indep {" << endl;

	if (size)	{
		f << "label = \"\\n\\nDo thi nhap tu file khong phai la rung.\"\n}";
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

		if (weighted)	{
			for (uint16_t i=0; i<vertices; ++i)
				for (uint16_t j=0; j<vertices; ++j)
					if (i<j && Has_edge_wgt(i, j))
						f << i+1 << " -- " << j+1 << " [label = \"" << wgt[i][j] << "\"]" << endl;
		}
		else	{
			for (uint16_t i=0; i<vertices; ++i)
				for (uint16_t j=0; j<vertices; ++j)
					if (i<j && Has_edge_wgt(i, j))
						f << i+1 << " -- " << j+1 << endl;
		}

		f << "label = \"\\n\\nTap doc lap lon nhat cua rung\\nvoi du lieu tu file\"\n}";
	}
	
	f.close();
	cout << "Xong." << endl;
}

//______________________________________________________________________________
// Tính big(v) tại v
void ugraph :: Calculate_big(uint16_t v)	{
	max_in[v] = weight[v];
	max_out[v] = 0.0;

	for (uint16_t u=0; u!=adj_lst[v].size(); ++u)	{
		max_in[v] += max_out[adj_lst[v][u]];
		max_out[v] += big[adj_lst[v][u]];
	}

	big[v] = max_in[v] > max_out[v] ? max_in[v] : max_out[v];
}

// Duyệt cây theo thứ tự sau
void ugraph :: Max_tree(uint16_t v)	{
	for (uint16_t u=0; u!=adj_lst[v].size(); ++u)
		Max_tree(adj_lst[v][u]);
	
	Calculate_big(v);
}

// Tìm tập độc lập có trọng số lớn nhất với đồ thị cây/rừng
void ugraph :: Find_max_weight_indep_set()	{
	// Khởi tạo mảng weight
	weight.resize(vertices);
	srand(uint16_t(time(0)));
	
	for (uint16_t i=0; i!=vertices; ++i)
		weight[i] = uint16_t( rand() ) % 10 + 1;
	
	max_in.resize(vertices);
	max_out.resize(vertices);
	big.resize(vertices);
	wgt_to_adj_lst();

	Max_tree(0);
	
	Print_runtime();
}

// Xây dựng mảng kết quả result
void ugraph :: Build_result()	{
	if (max_in[0] > max_out[0])
		result.push_back(0);

	for (uint16_t j=1; j!=vertices; ++j)	{
		// Tìm cha của j là i
		uint16_t i;
		bool found = false;

		for (i=0; i!=vertices; ++i)	{
			for (uint16_t k=0; k!=adj_lst[i].size(); ++k)
				if (adj_lst[i][k] == j)	{
					found = true;
					break;
				}

			if (found)
				break;
		}

		if (found)	{
			// Kiểm tra xem i có nằm trong result không
			bool in_result = false;

			for (uint16_t k=0; k!=result.size(); ++k)
				if (result[k] == i)	{
					in_result = true;
					break;
				}

			// Thêm j vào result nếu i chưa nằm trong result và max_in[j] > max_out[j]
			if (!in_result && max_in[j] > max_out[j])
				result.push_back(j);
		}
	}
}

// In kết quả tìm kiếm tập độc lập có trọng số lớn nhất ra file .out
void ugraph :: Print_max_weight_indep_set_to_out(string input_header)	{
	fstream f = New_output_file(input_header, "_Max_weight_indep", ".out");

	// Bắt đầu in kết quả
	if (big[0] == 0.0)
			f << "Do thi da cho khong phai la cay." << endl;
	else	{
		f << "Cac dinh trong tap doc lap trong so cuc dai " << big[0] << " la: " << endl;

		for (uint16_t i=0; i!=result.size(); ++i)
			f << result[i] + 1 << " ";

		f << endl;
	}

	f.close();
	cout << "Xong." << endl;
}

// In kết quả tìm kiếm tập độc lập có trọng số lớn nhất ra file .dot
void ugraph :: Print_max_weight_indep_set_to_dot(string input_header)	{
	fstream f = New_output_file(input_header, "_Max_weight_indep", ".dot");

	// Bắt đầu in file
	f << "graph " << input_header << "_Max_weight_indep {" << endl;

	if (big[0] == 0.0)	{
		f << "label = \"\\n\\nDo thi nhap tu file khong phai la cay.\"\n}";
	}
	else	{
		// Các đỉnh nằm trong tập kết quả được tô màu đỏ
		f << "node [style = filled, color = red]";
		for (uint16_t i=0; i!=result.size(); ++i)
			f << " " << result[i]+1 << "." << weight[result[i]];
		f << "\n";

		// Các đỉnh còn lại tô màu xanh
		f << "node [style = filled, color = green]";
		vector <uint16_t> b(vertices);

		for (uint16_t i=0; i!=vertices; ++i)
			b[i] = i;

		for (uint16_t i=0; i!=result.size(); ++i)
			b[result[i]] = UINT16_MAX;

		for (uint16_t i=0; i!=b.size(); ++i)
			if (b[i] != UINT16_MAX)
				f << " " << b[i]+1 << "." << weight[b[i]];
		f << "\n";
		
		if (weighted)	{
			for (uint16_t i=0; i<vertices; ++i)
				for (uint16_t j=0; j<vertices; ++j)	{
					if (i<j && Has_edge_wgt(i, j))
						f << i+1 << "." << weight[i] << " -- " << j+1 << "." << weight[j] 
						  << " [label = \"" << wgt[i][j] << "\"]" << endl;
				}
		}
		else	{
			for (uint16_t i=0; i<vertices; ++i)
				for (uint16_t j=0; j<vertices; ++j)	{
					if (i<j && Has_edge_wgt(i, j))
						f << i+1 << "." << weight[i] << " -- " << j+1 << "." << weight[j] << endl;
				}
		}

		f << "label = \"\\n\\nTap doc lap trong so cuc dai " << big[0] 
		  << "\\ncua cay voi du lieu tu file\"\n}";
	}
	
	f.close();
	cout << "Xong." << endl;
}

// Tìm tập độc lập cực đại về kích thước hoặc trọng số và hiển thị kết quả
void ugraph :: Find_max_indep_set(max_indep_alg alg, string output_header, output_type type)	{
	Initiate_indep_set();

	if (alg == MAX_SIZE)	{
		Find_max_size_indep_set();
		Print_runtime();
		
		if (type == OUT)
			Print_max_size_indep_set_to_out(output_header);
		else if (type == DOT)
			Print_max_size_indep_set_to_dot(output_header);
		else	{
			Print_max_size_indep_set_to_dot(output_header);
			Dot_to_bmp(output_header, "_Max_size_indep");
		}
	}
	else	{
		Find_max_weight_indep_set();
		Print_runtime();
		Build_result();

		if (type == OUT)
			Print_max_weight_indep_set_to_out(output_header);
		else if (type == DOT)
			Print_max_weight_indep_set_to_dot(output_header);
		else	{
			Print_max_weight_indep_set_to_dot(output_header);
			Dot_to_bmp(output_header, "_Max_weight_indep");
		}
	}
}