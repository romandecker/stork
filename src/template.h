#include <string>
#include <vector>
#include <map>
#include <sstream>

#include <v8.h>

namespace stork {

    class FileTemplate {
        
    public:
        FileTemplate( const FileTemplate& orig )
            : path_( orig.path_ ),
              javascript_( orig.javascript_ ),
              out_( orig.out_.str() ) {

        }
        static FileTemplate parse( const std::string& template_file );

        void instantiate(
                        const std::string& path,
                        const std::map<std::string, std::string>& params );

        std::string path() const {
            return this->path_;
        }

    private:
        FileTemplate( const std::string& path )
            : path_( path ),
              javascript_( "" ),
              out_() {
        }

        std::string path_;
        std::string javascript_;
        std::stringstream out_;

        static v8::Handle<v8::Value> emit_wrapper( const v8::Arguments& args );
        v8::Handle<v8::Value> emit( const v8::Arguments& args );


    };

    class Template {

    public:
        Template( const std::string& path );

        void instantiate( const std::string name,
                          const std::map<std::string, std::string>& params );

    private:
        std::string path_;
        std::vector<FileTemplate> templates_;

    };
}
