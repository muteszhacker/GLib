/*THÔNG TIN*********************************************************************
 *Tập tin		: write_file.h
 *Mô tả			: Các phương thức ghi đồ thị ra file DOT, BMP
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

//______________________________________________________________________________
// Mở file .dot mới, opt là tùy chọn phụ thuộc thuật toán
fstream graph :: New_output_file(string input_header, string opt, string extension)	{
	cout << "Luu ket qua ra file " << input_header << opt << extension << "..........";

	return fstream(input_header + opt + extension, ios :: out);
}

// Lưu đồ thị dưới dạng file .dot
void graph :: Print_graph_to_dot(string input_header)	{
	fstream f = New_output_file(input_header, "", ".dot");

	if (directed)
		f << "digraph " << input_header << " {" << endl;
	else
		f << "graph " << input_header << " {" << endl;

	if (directed)	{
		for (uint16_t i=0; i<vertices; ++i)
			for (uint16_t j=0; j<vertices; ++j)	{
				if (Has_edge_wgt(i, j))	{
					if (weighted)
						f << i+1 << " -> " << j+1 << " [label = \"" << wgt[i][j] << "\"]" << endl;
					else
						f << i+1 << " -> " << j+1 << endl;
				}
			}
	}
	else	{
		for (uint16_t i=0; i<vertices; ++i)
			for (uint16_t j=0; j<vertices; ++j)	{
				if (i<j && Has_edge_wgt(i, j))	{
					if (weighted)
						f << i+1 << " -- " << j+1 << " [label = \"" << wgt[i][j] << "\"]" << endl;
					else
						f << i+1 << " -- " << j+1 << endl;
				}
			}
	}

	f << "label = \"\\n\\nDo thi voi du lieu tu file\"\n}";
	f.close();
	cout << "Xong." << endl;
}

//______________________________________________________________________________
// Dịch từ file .dot sang hình ảnh .bmp, tùy chọn opt phụ thuộc thuật toán
void graph :: Dot_to_bmp(string input_header, string opt)	{
	cout << "Bien dich file " << input_header << opt << ".dot ra hinh anh..........";

	string command = "dot -Tbmp -o" + input_header + opt + ".bmp " + input_header + opt + ".dot";

	system(command.c_str());

	cout << "Xong." << endl;

	string out_name = input_header + opt + ".bmp ";
	system(out_name.c_str());
}

//______________________________________________________________________________
// In thông báo thời gian chạy thuật toán
void graph :: Print_runtime()	{
	finish_time = clock();
	cout << "Xong trong " 
		 << double(finish_time - start_time) / CLOCKS_PER_SEC << " s.\n";
}