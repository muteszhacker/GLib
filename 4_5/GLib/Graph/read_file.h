/*THÔNG TIN*********************************************************************
 *Tập tin		: read_file.h
 *Mô tả			: Các phương thức đọc tập tin txt và grf
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//______________________________________________________________________________
// Khởi tạo đồ thị đọc từ file
fstream graph :: Initiate_from_file(string input_header, input_type type)	{
	string input_file(input_header);
	if (type == TXT || type == W_TXT)
		input_file += ".txt";
	else if (type == GRF)
		input_file += ".grf";

	fstream f(input_file, ios :: in);
	if (!f)	{
		cout << "Loi: File khong ton tai." << endl;
		return f;
	}

	cout << "Doc du lieu do thi..........";

	// Đọc số đỉnh và số cạnh
	if (type == TXT || type == W_TXT)	{
		f >> vertices >> edges;
		Initiate_wgt(vertices);
		return f;
	}
	else if (type == GRF)	{
		char *line = new char[MAX_CHAR];

		while (!f.eof())	{
			f.getline(line, MAX_CHAR);
		
			if (line[1] == '\0')
				break;
			else
				++vertices;
		}

		--vertices;
		Initiate_wgt(vertices);
		return fstream(input_file, ios :: in);
	}
}

//______________________________________________________________________________
// Đọc dữ liệu đồ thị từ file txt
bool graph :: Read_txt(input_type type, string input_header)	{
	fstream f = Initiate_from_file(input_header, type);
	if (!f)
		return false;

	ver_t temp_1, temp_2;

	if (type == TXT)	{
		for (auto i=0; i!=edges; ++i)	{
			f >> temp_1 >> temp_2;
			wgt[temp_1-1][temp_2-1] = 1.0;
		}
	}
	else if (type = W_TXT)	{
		wgt_t temp_3;
		
		for (auto i=0; i!=edges; ++i)	{
			f >> temp_1 >> temp_2 >> temp_3;
			wgt[temp_1-1][temp_2-1] = temp_3;
		}
	}

	cout << "Xong." << endl;
	f.close();
	return true;
}

//______________________________________________________________________________
// Nhận diện từng đỉnh đọc vào xâu
char* graph :: Identify_vertex(char *edge_list_string, uint16_t &i)	{
	uint16_t count = 0;
	char *num = new char[10];

	num[0] = edge_list_string[i];
				
	while ( edge_list_string[i+1]>='0' && edge_list_string[i+1]<='9' )	{
		++count;
		++i;
		num[count] = edge_list_string[i];
	}
	num[count+1] = '\0';

	return num;
}

// Đọc danh sách đỉnh mà từ index có đường đi đến
void graph :: Read_all_vertices(fstream &f, uint16_t index, vector <edge> &edge_list)	{
	char *edge_list_string = new char[MAX_CHAR];

	f.getline(edge_list_string, MAX_CHAR);

	size_t len = strlen(edge_list_string);

	if (len)	{
		// Trích xuất các đỉnh
		uint16_t i=0;
	
		while (i != len)	{
			if (edge_list_string[i]>='0' && edge_list_string[i]<='9' )	{
				char *num = Identify_vertex(edge_list_string, i);
			
				// Lưu danh sách cạnh vào mảng edge_list
				edge e;
				e.start = index - 1;
				e.finish = uint16_t(atol(num)) - 1;
				edge_list.push_back(e);

				++edges;
			}			

			++i;
		}
	}
}

// Trả về khoảng cách theo công thức tọa độ giữa hai cạnh
wgt_t graph :: Distance(coord c1, coord c2)	{
	double dx = c1.x - c2.x, dy = c1.y - c2.y;

	return sqrt(dx*dx + dy*dy);
}

// Lưu độ dài cạnh vào mảng length
void graph :: Calc_length(vector <coord> list, vector <edge> edge_list)	{
	uint16_t u, v;

	for (uint16_t i=0; i!=edges; ++i)	{
		u = edge_list[i].start;
		v = edge_list[i].finish;

		wgt[u][v] = Distance(list[u], list[v]);
	}
}

// Đọc dữ liệu đồ thị từ file grf
bool graph :: Read_grf(string input_header)	{
	fstream f = Initiate_from_file(input_header);
	if (!f)
		return false;

	// Danh sách tọa độ các đỉnh
	vector <coord> list(vertices);
	// Danh sách các cạnh
	vector <edge> edge_list;
	edge_list.clear();

	while (!f.eof())	{
		// Đọc tên đỉnh
		uint16_t index = 0;

		f >> index;

		if (index == 0)
			break;

		// Đọc tọa độ đỉnh
		f >> list[index-1].x >> list[index-1].y;
		
		Read_all_vertices(f, index, edge_list);
	}
	
	Calc_length(list, edge_list);
	
	cout << "Xong." << endl;
	return true;
	f.close();
}