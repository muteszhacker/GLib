/*Giải thuật Ford-Bellman để tìm đường đi ngắn nhất****************************/
void PATH :: Ford_Bellman()	{
	/*Khởi tạo*/
	bool stop;
	int count = 0, i, j;
	
	before = new int*[1];
	before[0] = new int[Get_vertices()];
	min_len = new long*[1];
	min_len[0] = new long[Get_vertices()];

	for (int i=0; i<Get_vertices(); ++i)	{
		min_len[0][i] = MAX_LENG;
		before[0][i] = -1;
	}
	min_len[0][Get_start()] = 0;

	clock_t time_begin = clock();

	do	{
		stop = true;

		for (i=0; i<Get_vertices(); ++i)
			for (j=0; j<Get_vertices(); ++j)
				/*Nếu thấy d[j]>d[i]+a[i][j] thì tối ưu và lưu lại đường đi*/
					if (Get_length(i, j) && min_len[0][j] > min_len[0][i] + Get_length(i, j))	{
					min_len[0][j] = min_len[0][i] + Get_length(i, j);
					before[0][j] = i;
					stop=false;
				}

		++count;
	} while (!stop && count < Get_vertices() - 1);
	/*Dừng lại khi không cần tối ưu đỉnh nào nữa (stop==true) hoặc số lần lặp
	là vertices-1*/

	clock_t time_end = clock();
	cout << "Thuat toan chay trong " 
		 << (double)(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";
}/*Kết thúc hàm Ford_Bellman***************************************************/
