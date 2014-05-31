/*Giải thuật BFS để tìm đường đi***********************************************/
void PATH :: BFS()	{
	/*Khởi tạo*/
	int i, j, left = 0, right = 0;
	int *queue = new int[Get_vertices()];
	mark = new bool[Get_vertices()];
	before = new int[Get_vertices()];

	for (i=0; i<Get_vertices(); ++i)	{
		mark[i] = false;
		before[i] = -1;
		queue[i] = -1;
	}
	queue[0] = Get_start();
	mark[Get_start()] = true;
	
	clock_t time_begin = clock();	
	
	while (left <= right)	{
		/*Đẩy đỉnh i vào hàng đợi*/
		i = queue[ left++ ];

		/*Tìm trong các đỉnh lân cận của i, đỉnh j nào chưa được thăm thì cho 
		vào	tập hành trình*/ 
		for (j=0; j<Get_vertices(); ++j)
			if (Get_length(i, j) && !mark[j])	{
				queue[ ++right ] = j;
				mark[j] = true;
				before[j] = i;
			}
		
		/*Dừng ngay khi đi qua đỉnh đích*/
		if (mark[Get_destination()])
			break;
	}

	clock_t time_end = clock();
	cout << "Thuat toan chay trong " 
		<< (double)(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";

	delete[] queue;
}/*Kết thúc hàm BFS************************************************************/