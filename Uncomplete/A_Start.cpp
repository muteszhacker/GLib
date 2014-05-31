/*Hàm heuritic tính khoảng cách theo đường chim bay giữa các đỉnh**************/
int GRAPH :: Distance(EDGE l1, EDGE l2) {
	float dx = (float)(l1.x - l2.x), dy = (float)(l1.y - l2.y);

	return int( floor( sqrt(dx*dx + dy*dy) ) );
}/*Kết thúc hàm Distance*******************************************************/

/*Giải thuật A Star để tìm đường đi ngắn nhất**********************************/
void PATH :: A_Star()	{
	/*Khởi tạo*/
	int i, j;
	long min, *heuritic = new long[Get_vertices()], *estimate = new long[Get_vertices()];
	mark = new bool[Get_vertices()];
	before = new int[Get_vertices()];
	min_len = new long[Get_vertices()];

	for (i=0; i<Get_vertices(); ++i)	{
		mark[i] = false;
		before[i] = -1;
		min_len[i] = estimate[i] = INT_MAX;
		heuritic[i] = Distance(Get_location(i), Get_location(Get_destination()));
	}
    min_len[0] = 0;
    estimate[0] = heuritic[0] = 0;

    clock_t time_begin = clock();

	do {
		i = -1;
		min = INT_MAX;

		/*Tìm trong các đỉnh lân cận j đỉnh nào gần đỉnh 0 nhất*/
		for (j=0; j<Get_vertices(); ++j)
			if (!mark[j] && min > estimate[j])	{
				min = estimate[j];
				i = j;
			}

		if (i==-1)		break;

		for (j=0; j<Get_vertices(); ++j)
			if (Get_length(i, j) && 
				min_len[j] > min_len[i] + Get_length(i, j))	{
					min_len[j] = min_len[i] + Get_length(i, j);
				estimate[j] = heuritic[j] + min_len[j];
				before[j] = i;
			}

			mark[i] = true;
	} while (i != Get_destination());
	/*Dừng lại khi không cần tối ưu đỉnh nào nữa (i==-1) hoặc đã duyệt đến 
	đỉnh đích (i==destination)*/

	clock_t time_end = clock();
	cout << "Thuat toan chay trong " 
		<< (double)(time_end - time_begin) / CLOCKS_PER_SEC << " s.\n";

	delete[] heuritic;
	delete[] estimate;
}/*Kết thúc hàm A_Star*********************************************************/