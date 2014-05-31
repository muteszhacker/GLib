/*THÔNG TIN*********************************************************************
 *Tập tin		: initiate.h
 *Mô tả			: Các phương thức khởi tạo, cấp phát bộ nhớ thuộc tính mảng
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//______________________________________________________________________________
// Khởi tạo ma trận trọng số / kề
void graph :: Initiate_wgt(ver_t ver)	{
	wgt.resize(ver);

	for (auto i=0; i<ver; ++i)	{
		wgt[i].resize(ver);
		fill(wgt[i].begin(), wgt[i].end(), UINT16_MAX);
	}
}

// Khởi tạo danh sách cạnh
void graph :: Initiate_edg_lst(edg_t edg)	{
	edg_lst.resize(edg);
}

// Khởi tạo danh sách kề
void graph :: Initiate_adj_lst(ver_t ver)	{
	adj_lst.resize(ver);
}

// Khởi tạo ma trận final
void graph :: Initiate_final(ver_t ver)	{
	final.resize(ver);
}

// Khởi tạo ma trận result
void graph :: Initiate_result(ver_t ver)	{
	result.resize(ver);
}

//______________________________________________________________________________
// Xây dựng mảng adj_lst từ mảng wgt
void graph :: wgt_to_adj_lst(bool opt)	{
	Initiate_adj_lst(0);

	if (opt)	{
		for (uint16_t i=0; i<vertices; i++)	{
			vector <uint16_t> neighbor;

			for (uint16_t j=0; j<vertices; j++)
				if (wgt[i][j]!=UINT16_MAX)
					neighbor.push_back(j);
		
			adj_lst.push_back(neighbor);
		}
	}
	else	{
		for (uint16_t i=0; i<vertices; i++)	{
			vector <uint16_t> neighbor;
	
			for (uint16_t j=0; j<vertices; j++)
				if (i<j && Has_edge_wgt(i, j))
					neighbor.push_back(j);
		
			adj_lst.push_back(neighbor);
		}
	}
}