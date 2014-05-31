// Duyệt theo chiều sâu để đếm số thành phần liên thông************************/
void TRAVERSE :: BFS_to_count(uint16_t start)	{
	uint16_t i, left = 0, right = 0;
	vector <uint16_t> queue ( Get_vertices(), UINT16_MAX);
	queue[0] = start;

	while (left <= right)	{
		i = queue[ left++ ];

		for (uint16_t j=0; j!=Get_vertices(); ++j)
			if ( Get_length(i, j)>0.0 && group[j]==0 )	{
				queue[ ++right ] = j;
				group[j] = group[i];
			}
	}
}/*Kết thúc hàm BFS_to_count***************************************************/

/*Tìm các thành phần liên thông************************************************/
void TRAVERSE :: Find_connected_component()	{
	for (uint16_t i=0; i!=Get_vertices(); ++i)
		if (group[i] == 0)	{
			group[i] = (++group_count);
			BFS_to_count(i);
		}
}/*Kết thúc hàm Find_connected_component***************************************/

/*In thông báo kết thúc thuật toán đếm vùng liên thông*************************/
void TRAVERSE :: Final_count()	{
	time_end = clock();
	cout << "\nThuat toan duoc thuc hien trong " 
		<< (double)(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";
}/*Kết thúc hàm Final_count****************************************************/

/*In kết quả tìm vùng liên thông ra file***************************************/
void TRAVERSE :: Print_connected_components()	{
	cout << "\n\n\nLuu ket qua vao file: ";
	string file_name(MAX_FILE_NAME_LEN, ' ');
	cout.flush();
	cin >> file_name;

	fstream f(file_name, ios :: out);

	cout << "Dang luu ket qua...";

	if (group_count == 1)
		f << "Do thi da cho lien thong.\n";
	else	{
		f << "Co " << group_count << " thanh phan lien thong";

		for (uint16_t i=1; i<=group_count; ++i)	{
			f << "\nThanh phan " << i << " gom cac dinh: ";
			for (uint32_t j=0; j!=Get_vertices(); ++j)
				if (group[j] == i)
					f << j << " ";
		}
	}

	cout << "\nDa luu xong ket qua tim kiem thanh phan lien thong.\n";
	f.close();
}/*Kết thúc hàm Print_connected_components*************************************/
