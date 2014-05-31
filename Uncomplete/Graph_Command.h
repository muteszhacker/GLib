/*Thông tin*********************************************************************
 *Tên tập tin	: Graph_command.h
 *Mô tả			: Thư viên các hàm giao tiếp với đồ thị
 *Phiên bản		: 6.0
 *Ngày tạo		: 28/09/2012
 *Cập nhật cuối	: 10/10/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

/*Khai báo các hàm*************************************************************/
void Cmd_BFS(char *dest_folder, _finddata_t file_info);
void Cmd_DFS(char *dest_folder, _finddata_t file_info);
void Cmd_Topo(char *dest_folder, _finddata_t file_info);
void Cmd_Dijkstra(char *dest_folder, _finddata_t file_info);
void Cmd_Cover(char *dest_folder, _finddata_t file_info);

void Find_and_do(char *old_path, char *dest_folder, _finddata_t file_info, 
				 intptr_t search_handle, char *algol_name);
void Cmd_graph(char *parameter);

/*Command BFS - Duyệt đồ thị theo chiều rộng***********************************/
void Cmd_BFS(char *dest_folder, _finddata_t file_info)	{
	TRAVERSE t;

	if (t.Initiate_traverse(false, file_info.name))	{
		t.BFS(0);

		t.Final_traverse();
			
		_chdir(dest_folder);
		t.Print_traverse(file_info.name, 0);
		t.Print_traversed_graph(file_info.name, 0);
	}
}/*Kết thúc hàm Cmd_BFS********************************************************/

/*Command DFS - Duyệt đồ thị theo chiều sâu************************************/
void Cmd_DFS(char *dest_folder, _finddata_t file_info)	{
	TRAVERSE t;

	if (t.Initiate_traverse(false, file_info.name))	{
		t.DFS(0);

		t.Final_traverse();
			
		_chdir(dest_folder);
		t.Print_traverse(file_info.name, 1);
		t.Print_traversed_graph(file_info.name, 1);
	}
}/*Kết thúc hàm Cmd_DFS********************************************************/

/*Command Topo - Đánh số đồ thị dùng thuật toán Topo***************************/
void Cmd_Topo(char *dest_folder, _finddata_t file_info)	{
	DAG d;

	if (d.Initiate_Topo(false, file_info.name))	{
		d.Topological_order();
		d.Final_Topo();

		_chdir(dest_folder);
		d.Print_Topo(file_info.name);
		d.Print_new_graph_to_dot(file_info.name);
	}
}/*Kết thúc hàm Cmd_Topo*******************************************************/

/*Command Dijkstra - Tìm đường đi ngắn nhất dùng thuật toán Dijkstra***********/
void Cmd_Dijkstra(char *dest_folder, _finddata_t file_info)	{
	PATH p;

	if (p.Initiate_Find(false, 10, file_info.name))	{
		p.Dijkstra();
		p.Final_Find();

		_chdir(dest_folder);
		p.Print_result(10, file_info.name);
		p.Print_dot_result(file_info.name, 10);
	}
}/*Kết thúc hàm Cmd_Dijkstra***************************************************/

/*Command Prim - Tìm cây khung nhỏ nhất dùng thuật toán Prim*******************/
void Cmd_Prim(char *dest_folder, _finddata_t file_info)	{
	FRAME f;

	if (f.Initiate_Frame(false, 0, file_info.name))	{
		f.Prim();
		f.Final_Frame();

		_chdir(dest_folder);
		f.Print_Frame(0, file_info.name);
		f.Print_dot_frame(file_info.name, 0);
	}
}/*Kết thúc hàm Cmd_Prim*******************************************************/

/*Command Cover - Tìm Phủ đỉnh kích thước không lớn hơn k của đồ thị***********/
void Cmd_Cover(char *dest_folder, _finddata_t file_info)	{
	COVER c;

	if (c.Initiate_Cover(false, file_info.name))	{
		c.Find_neighbors();
		c.Final_Cover();
		
		_chdir(dest_folder);
		c.Print_Cover(file_info.name);
		c.Print_Cover_to_dot(file_info.name);
	}
}/*Kết thúc hàm Cmd_Prim*******************************************************/

/*Tìm, đọc và thực hiện thuật toán từ file grf*********************************/
void Find_and_do(char *old_path, char *dest_folder, _finddata_t file_info, 
				 intptr_t search_handle, char *algol_name)	{
	uint16_t counter = 0;

	do	{
		_chdir(old_path);
		++counter;
							
		cout << "Tap tin: ";
		SetTextColor(2);
		cout << file_info.name << "\n";
		SetTextColor(6);

		if (!strcmp(algol_name, "BFS"))
			Cmd_BFS(dest_folder, file_info);
		else if (!strcmp(algol_name, "DFS"))
			Cmd_DFS(dest_folder, file_info);
		else if (!strcmp(algol_name, "Topo"))
			Cmd_Topo(dest_folder, file_info);
		else if (!strcmp(algol_name, "Dijkstra"))
			Cmd_Dijkstra(dest_folder, file_info);
		else if (!strcmp(algol_name, "Prim"))
			Cmd_Prim(dest_folder, file_info);
		else if (!strcmp(algol_name, "Cover"))
			Cmd_Cover(dest_folder, file_info);
		else	{
			Error(13);
			break;
		}
	} while(!_findnext(search_handle, &file_info));

	SetTextColor(6);
	if (counter)
		cout << counter << " file grf da duoc doc va xuat ket qua ra thu muc " 
			 << dest_folder << ".\n";
	else	cout << "\nKhong co tap tin grf nao.\n";
}/*Kết thúc hàm Find_and_go****************************************************/

/*Command graph - Các lệnh với đồ thị đọc từ file******************************/
void Cmd_graph(char *parameter)	{
	char algol_name[20];
	char dest_folder[MAX_PATH_LEN];
	algol_name[0] = dest_folder[0] = '\0';

	if (parameter[0] == '-' && parameter[1] == '>')	{
		int i = 2;
		while (parameter[i] == ' ')
			++i;

		int j = 0;
		while (parameter[i] != '\0')
			dest_folder[j++] = parameter[i++];
		dest_folder[j] = '\0';
	}

	if (!Trim(parameter, algol_name, dest_folder, 0))			
		return;

	char old_path[MAX_PATH_LEN];
	strcpy(old_path, _getcwd(NULL, 0));
	_mkdir(dest_folder);

	// Tìm tất cả các file .grf trong thu muc hien hanh
	_finddata_t file_info;
	intptr_t search_handle = _findfirst("*.grf", &file_info);

	if (search_handle == -1)		Error(3);
	else	{
		GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
		WORD wAttributes = screen_buffer_info.wAttributes;
		
		Find_and_do(old_path, dest_folder, file_info, search_handle, algol_name);

		_findclose(search_handle);
	
		_chdir(old_path);

		SetConsoleTextAttribute(hConsole, wAttributes);
	}
}/*Kết thúc hàm Cmd_graph******************************************************/
