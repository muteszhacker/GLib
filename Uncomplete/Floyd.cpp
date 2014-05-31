/*Giải thuật Floyd để tìm đường đi ngắn nhất***********************************/
void PATH :: Floyd()	{
	/*Khởi tạo*/
	int i, j, k;

	size_before = Get_vertices();
	before = new int*[size_before];
	for (int i=0; i<Get_vertices(); ++i)
		before[i] = new int[Get_vertices()];

	size_min_len = Get_vertices();
	min_len = new long*[size_min_len];
	for (int i=0; i<Get_vertices(); ++i)
		min_len[i] = new long[Get_vertices()];

	for (i=0; i<Get_vertices(); ++i)
		for (j=0; j<Get_vertices(); ++j)	{
			if (Get_length(i, j))
				before[i][j] = i;
			else	before[i][j] = -1;

			min_len[i][j] = Get_length(i, j);
		}			

		clock_t time_begin = clock();

		for (k=0; k<Get_vertices(); ++k)
			for (i=0; i<Get_vertices(); ++i)
				for (j=0; j<Get_vertices(); ++j)
					/*Nếu d[i][j]==0 hoặc d[i][j] > d[i][k] + d[k][j] thì tối ưu */
						if (min_len[i][k] && min_len[k][j] && (!min_len[i][j] ||
							min_len[i][j] > min_len[i][k] + min_len[k][j])	)	{
								min_len[i][j] = min_len[i][k] + min_len[k][j];
								before[i][j] = before[k][j];
						}

						clock_t time_end = clock();
						cout << "Thuat toan chay trong " 
							<< (double)(time_end-time_begin)/CLOCKS_PER_SEC << " s.\n";
}/*Kết thúc hàm Floyd**********************************************************/