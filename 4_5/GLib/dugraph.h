/*THÔNG TIN*********************************************************************
 *Tập tin		: dugraph.h
 *Mô tả			: Thư viện đồ thị có hướng, không trọng số
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//____________________LỚP ĐỒ THỊ CÓ HƯỚNG, KHÔNG TRỌNG SỐ_______________________
class dugraph : public dgraph	{
public:
	//__________________________PHƯƠNG THỨC KHỞI TẠO____________________________

	// Phương thức khởi tạo mặc định
	dugraph();
	// Khởi tạo đồ thị với số đỉnh xác định
	dugraph(ver_t ver);
	// Khởi tạo đồ thị nhập từ file
	dugraph(input_type type, string input_header);
	// Khởi tạo đồ thị từ một ma trận đã có
	dugraph(vector < vector <wgt_t> > mtr);
};

//______________________________________________________________________________
// Phương thức khởi tạo mặc định
dugraph :: dugraph()	{
	weighted = false;
}

// Khởi tạo đồ thị với số đỉnh xác định
dugraph :: dugraph(ver_t ver)	{
	vertices = ver;
	weighted = false;
	Initiate_wgt(ver);
}

// Khởi tạo đồ thị từ file
dugraph :: dugraph(input_type type, string input_header)	{
	weighted = false;

	if (type == TXT)
		Read_txt(type, input_header);
	else if (type == GRF)	{
		Read_grf(input_header);
	
		for (auto i=0; i<wgt.size(); ++i)
			for (auto j=0; j<wgt[i].size(); ++j)	{
				if (Has_edge_wgt(i, j))
					wgt[i][j] = 1;
				}
	}
}

// Khởi tạo đồ thị từ một ma trận đã có
dugraph :: dugraph(vector < vector <wgt_t> > mtr)	{
	weighted = false;

	Initiate_wgt(vertices);

	for (auto i=0; i<vertices; ++i)
		for (auto j=0; j<vertices; ++j)	{
			if (mtr[i][j] != UINT16_MAX)
				++edges;
			wgt[i][j] = mtr[i][j];
		}
}