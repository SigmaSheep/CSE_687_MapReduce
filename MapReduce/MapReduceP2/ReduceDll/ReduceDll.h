
class R
{
public:
	ReduceDll() {};
	~ReduceDll() {};
	virtual void reduceFunction(const std::vector<std::vector<std::string>> input_vector, void(*exporting)(const std::vector<std::vector<std::string>>, std::string), const std::string out_file_name) {};
};
#endif
