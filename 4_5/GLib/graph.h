/*THÔNG TIN*********************************************************************
 *Tập tin		: graph.h
 *Mô tả			: Thư viện đồ thị
 *Ngày tạo		: 16/11/2012
 *Cập nhật cuối	: 18/11/2012
 *Trình dịch	: Microsoft Visual C++ 11.0
 *Tác giả		: Vũ Văn Hiệp
 *Thư điện tử	: muteszhacker@gmail.com
*******************************************************************************/

# define MAX_CHAR 500

//___________________________KHAI BÁO KIỂU DỮ LIỆU MỚI__________________________

// Kiểu đỉnh
typedef uint16_t ver_t;
// Kiểu cạnh
typedef uint32_t edg_t;
// Kiểu trọng số
typedef double wgt_t;
// Kiểu cạnh không trọng số
typedef struct	{
	uint16_t start, finish;
} edge;
// Kiểu cạnh có trọng số
typedef struct	{
	uint16_t start, finish;
	double weight;
} w_edge;
// Kiểu tọa độ đỉnh
typedef struct	{
	double x, y;
} coord;
// Phương pháp biểu diễn đồ thị
enum show_method	{
	MATRIX,
	EDGE_LIST,
	ADJACENCY_LIST
};
// Kiểu tập tin dữ liệu đồ thị đầu vào
enum input_type	{
	TXT,
	W_TXT,
	GRF
};
// Kiểu tập tin dữ liệu xuất ra
enum output_type	{
	OUT,
	DOT,
	BMP
};
// Các thuật toán duyệt đồ thị
enum traverse_algol		{
	DFS_ALG,
	BFS_ALG
};
// Các thuật toán tìm cây khung nhỏ nhất
enum min_span_tree_alg	{
	PRIM
};
// Các thuật toán tìm đường đi ngắn nhất
enum shortest_path_alg	{
	DIJKSTRA
};
// Các thuật toán tìm tập độc lập cực đại về số đỉnh hay trọng số
enum max_indep_alg	{
	MAX_SIZE,
	MAX_WEIGHT
};

//________________________________LỚP ĐỒ THỊ____________________________________
class graph	{
public:
	//_______________________________THUỘC TÍNH_________________________________

	ver_t vertices;					// Số đỉnh
	edg_t edges;					// Số cạnh
	show_method method;				// Phương thức biểu diễn đồ thị đang dùng
	bool directed;					// Đồ thị có hướng hay không
	bool weighted;					// Đồ thị có trọng số hay không

	//________________________MẢNG BIỂU DIỄN ĐỒ THỊ_____________________________

	vector < vector <wgt_t> > wgt;		// Ma trận trọng số / kề
	vector <edge> edg_lst;				// Danh sách cạnh
	vector < vector <ver_t> > adj_lst;	// Danh sách kề liên kết

	//__________________THUỘC TÍNH DÙNG KHI CHẠY THUẬT TOÁN_____________________

	vector <bool> final;				// Mảng đánh dấu đỉnh đã được xét
	vector <ver_t> result;				// Mảng lưu kết quả
	clock_t start_time;					// Thời gian bắt đầu 
	clock_t finish_time;				// Thời gian kết thúc
	uint16_t k;							// Kích thước phủ đỉnh

	//__________________________PHƯƠNG THỨC KHỞI TẠO____________________________

	// Phương thức khởi tạo mặc định
	graph();

	//_____________________________KHỞI TẠO MẢNG________________________________

	// Khởi tạo ma trận trọng số / kề
	void Initiate_wgt(ver_t ver);
	// Khởi tạo danh sách cạnh
	void Initiate_edg_lst(edg_t edg);
	// Khởi tạo danh sách kề
	void Initiate_adj_lst(ver_t ver);
	// Khởi tạo mảng final
	void Initiate_final(ver_t ver);
	// Khởi tạo mảng result
	void Initiate_result(ver_t ver);
	//__________________________________________________________________________
	// Xây dựng mảng adj_lst từ mảng wgt
	void wgt_to_adj_lst(bool opt = false);

	//________________________ĐỌC DỮ LIỆU ĐỒ THỊ TỪ FILE________________________

	// Khởi tạo đồ thị đọc từ file
	fstream Initiate_from_file(string input_header, input_type type = GRF);
	//__________________________________________________________________________
	// Đọc dữ liệu đồ thị từ file txt
	bool Read_txt(input_type type, string input_header);
	//__________________________________________________________________________
	// Nhận diện từng đỉnh đọc vào xâu
	char* Identify_vertex(char *edge_list_string, uint16_t &i);
	// Đọc danh sách đỉnh mà từ index có đường đi đến
	void Read_all_vertices(fstream &f, uint16_t index, vector <edge> &edge_list);
	// Trả về khoảng cách theo công thức tọa độ giữa hai cạnh
	wgt_t Distance(coord c1, coord c2);
	// Lưu độ dài cạnh vào mảng length
	void Calc_length(vector <coord> list, vector <edge> edge_list);
	// Đọc dữ liệu đồ thị từ file grf
	bool Read_grf(string input_header);

	//____________________KIỂM TRA CẠNH CÓ TRONG ĐỒ THỊ_________________________

	// Kiểm tra có cạnh (i, j) hay không trong ma trận kề / trọng số
	bool Has_edge_wgt(ver_t i, ver_t j);
	// Kiểm tra có cạnh (i, j) hay không trong danh sách cạnh
	bool Has_edge_edg_lst(ver_t i, ver_t j);
	// Kiểm tra có cạnh (i, j) hay không trong danh sách kề
	bool Has_edge_adj_lst(ver_t i, ver_t j);
	// Kiểm tra có cạnh (i, j) hay không
	bool Has_edge(ver_t i, ver_t j);

	//___________________________THÊM CẠNH VÀO ĐỒ THỊ___________________________

	// Thêm cạnh (i, j) trong ma trận kề / trọng số
	bool Add_edge_wgt(ver_t i, ver_t j, wgt_t value);
	// Thêm cạnh (i, j) trong danh sách cạnh
	bool Add_edge_edg_lst(ver_t i, ver_t j);
	// Thêm cạnh (i, j) trong danh sách kề
	bool Add_edge_adj_lst(ver_t i, ver_t j);
	// Thêm cạnh (i, j) cho đồ thị
	bool Add_edge(ver_t i, ver_t j, wgt_t value = 1.0) ;

	//__________________________LOẠI BỎ CẠNH KHỎI ĐỒ THỊ________________________

	// Loại bỏ cạnh (i, j) trong ma trận kề / trọng số
	bool Remove_edge_wgt(ver_t i, ver_t j);
	// Loại bỏ cạnh (i, j) trong danh sách cạnh
	bool Remove_edge_edg_lst(ver_t i, ver_t j);
	// Loại bỏ cạnh (i, j) trong danh sách kề
	bool Remove_edge_adj_lst(ver_t i, ver_t j);
	// Loại bỏ cạnh (i, j) cho đồ thị
	bool Remove_edge(ver_t i, ver_t j) ;

	//__________________________IN CÁC CẠNH CỦA ĐỒ THỊ__________________________

	// In các cạnh của đồ thị trong ma trận kề / trọng số
	void Print_edges_wgt();
	// In các cạnh của đồ thị trong danh sách cạnh
	void Print_edges_edg_lst();
	// In các cạnh của đồ thị trong danh sách kề
	void Print_edges_adj_lst();
	// In các cạnh của đồ thị
	void Print_edges();
	//__________________________________________________________________________
	// In các đỉnh của đồ thị
	void Print_vertices();

	//__________________________GHI KẾT QUẢ RA FILE_____________________________

	// Mở file .dot mới, opt là tùy chọn phụ thuộc thuật toán
	fstream New_output_file(string input_header, string opt, string extension);
	// Lưu đồ thị dưới dạng file .dot
	void Print_graph_to_dot(string input_header);
	// Dịch từ file .dot sang hình ảnh .bmp, tùy chọn opt phụ thuộc thuật toán
	void Dot_to_bmp(string input_header, string opt);
	//__________________________________________________________________________
	// In thông báo thời gian chạy thuật toán
	void Print_runtime();
	//__________________________________________________________________________
	// Xuất đồ thị ra tập tin dot hoặc bmp
	void Export_graph(string output_header, output_type type);
	//________________________________DUYỆT ĐỒ THỊ______________________________

	// Khởi tạo cho thuật toán duyệt
	void Initiate_traverse();
	// Duyệt theo chiều rộng
	void BFS(ver_t start);
	// Duyệt theo chiều sâu
	void DFS(ver_t ver);
	// In kết quả duyệt ra file
	void Print_traverse_to_out(string input_header, string opt);
	// In đồ thị với thứ tự duyệt các đỉnh
	void Print_traverse_to_dot(string input_header, string opt);
	// Duyệt đồ thị và hiển thị kết quả
	void Traverse(traverse_algol alg, string output_header, output_type type);

	//________________________________TÌM PHỦ ĐỈNH______________________________

	// Khởi tạo thuật toán tìm lớp phủ đỉnh kích thước không lớn hơn k
	void Initiate_cover();
	// Tìm lớp phủ đỉnh kích thước không lớn hơn k-1
	bool Vertex_cover(vector <vector <uint16_t> > temp, uint16_t not, uint16_t ver);
	// In kết quả tìm kiếm lớp phủ đỉnh ra file .out
	void Print_cover_to_out(string input_header);
	// In kết quả tìm kiếm lớp phủ đỉnh ra file .dot
	void Print_cover_to_dot(string input_header);
	// Tìm phủ đỉnh và hiển thị kết quả
	void Find_vertex_cover(string output_header, output_type type, ver_t max_size);
};

//______________________________________________________________________________
// Phương thức khởi tạo mặc định
graph :: graph()	{
	vertices = 0;
	edges = 0;
	method = MATRIX;
}

//______________________________________________________________________________
# include "Graph/initiate.h"
# include "Graph/read_file.h"
# include "Graph/change_edge.h"
# include "Graph/write_file.h"
# include "Graph/traverse.h"
# include "Graph/vertex_cover.h"
