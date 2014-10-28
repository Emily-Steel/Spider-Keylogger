#ifndef Project_JSONParser_h
# define Project_JSONParser_h

class JSONParser: public IReadable
{
public:
    JSONParser();
    ~JSONParser();
    
    virtual void put(const std::string &key, const std::string &value);
    virtual void get(const std::string &key, std::string &value);
    
    virtual void getReadable(const std::string &);
    virtual void setReadable(std::string &);
    
private:
    
};

#endif
