/*THÔNG TIN*********************************************************************
 *Tập tin		: change_edge.h
 *Mô tả			: Các phương thức thay đổi thông cạnh
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//______________________________________________________________________________
// Kiểm tra có cạnh (i, j) hay không trong ma trận kề / trọng số
bool graph :: Has_edge_wgt(ver_t i, ver_t j)	{
	return (wgt[i][j] != UINT16_MAX);
}

// Kiểm tra có cạnh (i, j) hay không trong danh sách cạnh
bool graph :: Has_edge_edg_lst(ver_t i, ver_t j)	{
	for (auto k=0; k<edg_lst.size(); ++k)
		if (edg_lst[k].start == i && edg_lst[k].finish == j)
			return true;
	
	return false;
}

// Kiểm tra có cạnh (i, j) hay không trong danh sách kề
bool graph :: Has_edge_adj_lst(ver_t i, ver_t j)	{
	for (auto k=0; k<adj_lst[i].size(); ++k)
		if (adj_lst[i][k] == j)
			return true;

	return false;
}

// Kiểm tra có cạnh (i, j) hay không
bool graph :: Has_edge(ver_t i, ver_t j)	{
	if (i==0 || j==0 || i==j || i>vertices || j>vertices)
		return false;

	--i;
	--j;

	if (method == MATRIX)
		return Has_edge_wgt(i, j);
	else if (method == EDGE_LIST)
		return Has_edge_edg_lst(i, j);
	else if (method == ADJACENCY_LIST)
		return Has_edge_adj_lst(i, j);
}

//______________________________________________________________________________
// Thêm cạnh (i, j) trong ma trận kề / trọng số
bool graph :: Add_edge_wgt(ver_t i, ver_t j, wgt_t value)	{
	if (!Has_edge_wgt(i, j))	{
		wgt[i][j] = value;

		if (!directed)
			wgt[j][i] = value;

		++edges;
		return true;
	}
	
	return false;
}

// Thêm cạnh (i, j) trong danh sách cạnh
bool graph :: Add_edge_edg_lst(ver_t i, ver_t j)	{
	if (!Has_edge_edg_lst(i, j))	{
		edge e;
		e.start = i;
		e.finish = j;
			
		edg_lst.push_back(e);
		++edges;
		return true;
	}
	
	return false;
}

// Thêm cạnh (i, j) trong danh sách kề
bool graph :: Add_edge_adj_lst(ver_t i, ver_t j)	{
	if (!Has_edge_adj_lst(i, j))	{
		adj_lst[i].push_back(j);
		++edges;
		return true;
	}
	
	return false;
}

// Thêm cạnh (i, j) cho đồ thị
bool graph :: Add_edge(ver_t i, ver_t j, wgt_t value)	{
	if (i==0 || j==0 || i==j || i>vertices || j>vertices)
		return false;

	if (!directed)	{
		if (Has_edge(j, i))
			return false;
	}

	--i;
	--j;

	if (method == MATRIX)
		return Add_edge_wgt(i, j, value);
	else if (method == EDGE_LIST)
		return Add_edge_edg_lst(i, j);
	else if (method == ADJACENCY_LIST)
		return Add_edge_adj_lst(i, j);
}

//______________________________________________________________________________
// Loại bỏ cạnh (i, j) trong ma trận kề / trọng số
bool graph :: Remove_edge_wgt(ver_t i, ver_t j)	{
	if (Has_edge_wgt(i, j))	{
		wgt[i][j] = UINT16_MAX;

		if (!directed)
			wgt[j][i] = UINT16_MAX;

		--edges;
		return true;
	}
	
	return false;
}

// Loại bỏ cạnh (i, j) trong danh sách cạnh
bool graph :: Remove_edge_edg_lst(ver_t i, ver_t j)	{
	for (auto k=0; k<edg_lst.size(); ++k)
		if (edg_lst[k].start == i && edg_lst[k].finish == j)	{
			edg_lst.erase(edg_lst.begin() + k);
			--edges;
			return true;
		}

	return false;
}

// Loại bỏ cạnh (i, j) trong danh sách kề
bool graph :: Remove_edge_adj_lst(ver_t i, ver_t j)	{
	for (auto k=0; k<adj_lst[i].size(); ++k)
		if (adj_lst[i][k] == j)	{
			adj_lst[i].erase(adj_lst[i].begin() + k);
			--edges;
			return true;
		}

	return false;
}

// Loại bỏ cạnh (i, j) cho đồ thị
bool graph :: Remove_edge(ver_t i, ver_t j)	{
	if (i==0 || j==0 || i==j || i>vertices || j>vertices)	{
		return false;
	}

	--i;
	--j;

	if (method == MATRIX)
		return Remove_edge_wgt(i, j);
	else if (method == EDGE_LIST)
		return Remove_edge_edg_lst(i, j);
	else if (method == ADJACENCY_LIST)
		return Remove_edge_adj_lst(i, j);
}

//______________________________________________________________________________
// In các cạnh của đồ thị trong ma trận kề / trọng số
void graph :: Print_edges_wgt()	{
	if (directed)	{
		if (weighted)	{
			for (auto i=0; i<vertices; ++i)
				for (auto j=0; j<vertices; ++j)
					if (Has_edge_wgt(i, j))
						cout << i + 1 << " -- " << wgt[i][j] << " -> " << j+1 << endl;
		}
		else	{
			for (auto i=0; i<vertices; ++i)
				for (auto j=0; j<vertices; ++j)
					if (Has_edge_wgt(i, j))
						cout << i + 1 << " ---> " << j+1 << endl;
		}
	}
	else	{
		if (weighted)	{
			for (auto i=0; i<vertices; ++i)
				for (auto j=0; j<vertices; ++j)
					if (i<j && Has_edge_wgt(i, j))
						cout << i + 1 << " <- " << wgt[i][j] << " -> " << j+1 << endl;
		}
		else	{
			for (auto i=0; i<vertices; ++i)
				for (auto j=0; j<vertices; ++j)
					if (i<j && Has_edge_wgt(i, j))
						cout << i + 1 << " <--> " << j+1 << endl;
		}
	}
}

// In các cạnh của đồ thị trong danh sách cạnh
void graph :: Print_edges_edg_lst()	{
	if (!directed && !weighted)	{
		for (auto i=0; i<edg_lst.size(); ++i)
			if (Has_edge_edg_lst(edg_lst[i].start, edg_lst[i].finish))
				cout << edg_lst[i].start + 1 << " <--> " << edg_lst[i].finish + 1 << endl;
	}
}

// In các cạnh của đồ thị trong danh sách kề
void graph :: Print_edges_adj_lst()	{
	if (!directed && !weighted)	{
		for (auto i=0; i<adj_lst.size(); ++i)
			for (auto j=0; j<adj_lst[i].size(); ++j)
				if (Has_edge_adj_lst(i, adj_lst[i][j]))
					cout << i + 1 << " <--> " << adj_lst[i][j] + 1 << endl;
	}
}

// In các cạnh của đồ thị
void graph :: Print_edges()	{
	cout << "Cac canh cua do thi: "<< endl;

	if (method == MATRIX)
		return Print_edges_wgt();
	else if (method == EDGE_LIST)
		return Print_edges_edg_lst();
	else if (method == ADJACENCY_LIST)
		return Print_edges_adj_lst();

	cout << endl;
}

//______________________________________________________________________________
// In các đỉnh của đồ thị
void graph :: Print_vertices()	{
	cout << "Cac dinh cua do thi: "<< endl;

	for (auto i=0; i<vertices; ++i)
		cout << i+1 << " ";

	cout << endl;
}

// Xuất đồ thị ra tập tin dot hoặc bmp
void graph :: Export_graph(string output_header, output_type type)	{
	if (type == DOT)	{
		Print_graph_to_dot(output_header);
	}
	else if (type == BMP)	{
		Print_graph_to_dot(output_header);
		Dot_to_bmp(output_header, "");
	}
}