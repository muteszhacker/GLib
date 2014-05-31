/*THÔNG TIN*********************************************************************
 *Tập tin		: uugraph.h
 *Mô tả			: Thư viện đồ thị vô hướng, không trọng số
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//______________________LỚP ĐỒ THỊ VÔ HƯỚNG, KHÔNG TRỌNG SỐ_____________________
class uugraph : public ugraph	{
public:
	//__________________________PHƯƠNG THỨC KHỞI TẠO____________________________

	// Phương thức khởi tạo mặc định
	uugraph();
	// Khởi tạo đồ thị với số đỉnh xác định
	uugraph(ver_t ver);
	// Khởi tạo đồ thị nhập từ file
	uugraph(input_type type, string input_header);
	// Khởi tạo đồ thị từ một ma trận / danh sách kề đã có
	uugraph(vector < vector <wgt_t> > mtr);
};

//______________________________________________________________________________
// Phương thức khởi tạo mặc định
uugraph :: uugraph()	{
	weighted = false;
}

/*Khởi tạo đồ thị với số đỉnh xác định*/
uugraph :: uugraph(ver_t ver)	{
	vertices = ver;
	weighted = false;
	Initiate_wgt(ver);
}

// Khởi tạo đồ thị với số đỉnh xác định
uugraph :: uugraph(input_type type, string input_header)	{
	weighted = false;

	if (type == TXT)
		Read_txt(type, input_header);
	else if (type == GRF)	{
		Read_grf(input_header);

		for (auto i=0; i<wgt.size(); ++i)
			for (auto j=0; j<wgt[i].size(); ++j)
				if (Has_edge_wgt(i, j))
					wgt[i][j] = 1;
	}

	for (auto i=0; i<wgt.size(); ++i)
		for (auto j=0; j<wgt[i].size(); ++j)
			if (Has_edge_wgt(i, j))
				wgt[j][i] = wgt[i][j];
}

// Khởi tạo đồ thị từ một ma trận / danh sách kề đã có
uugraph :: uugraph(vector < vector <wgt_t> > mtr)	{
	weighted = false;

	Initiate_wgt(vertices);

	for (auto i=0; i<vertices; ++i)
		for (auto j=0; j<vertices; ++j)	{
			if (mtr[i][j] != UINT16_MAX)
				++edges;
			wgt[i][j] = mtr[i][j];
		}
}