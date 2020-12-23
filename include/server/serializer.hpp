#ifndef ASCIINEM_SERVER_SERIALIZER_HPP
#define ASCIINEM_SERVER_SERIALIZER_HPP

#include <cereal/archives/xml.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/utility.hpp>
#include <string_view>

namespace asciinem::server
{

class serializer
{
public:
    template <class T>
    static auto serialize( const T& data ) -> std::string
    {
        auto ss = std::stringstream {};

        {
            auto archive = cereal::XMLOutputArchive( ss );
            archive( data );
        }

        return ss.str();
    }

    template <class T>
    static auto deserialize( const std::string& data ) -> T
    {
        auto make_stream = [ &data ]() {
            auto ss = std::stringstream { data };
            auto login = std::string {};
            ss >> login;

            return ss;
        };

        auto tmp = T {};
        auto ss = make_stream();

        {
            auto archive = cereal::XMLInputArchive( ss );
            archive( tmp );
        }

        return tmp;
    }

    static auto is_complete( std::string_view data ) -> bool
    {
        return data.find( "<cereal>" ) != std::string::npos &&
               data.find( "</cereal>" ) != std::string::npos;
    }
};

} // namespace asciinem::server

#endif // ASCIINEM_SERVER_SERIALIZER_HPP
