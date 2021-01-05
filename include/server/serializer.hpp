#ifndef ASCIINEM_SERVER_SERIALIZER_HPP
#define ASCIINEM_SERVER_SERIALIZER_HPP

#include <cereal/archives/xml.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/utility.hpp>
#include <spdlog/spdlog.h>
#include <string_view>

namespace asciinem::server
{

class serializer
{
public:
    template <class T>
    static auto serialize( const T& data ) -> std::string
    {
        auto ss = std::ostringstream {};

        {
            auto archive = cereal::XMLOutputArchive( ss );
            archive( data );
        }

        return ss.str();
    }

    template <class T>
    static auto deserialize( const std::string& data ) -> T
    {
        spdlog::trace( "Deserializing: '{}'", data );

        auto tmp = T {};
        auto ss = std::istringstream { data };

        try
        {
            auto archive = cereal::XMLInputArchive( ss );
            archive( tmp );
        }
        catch ( std::exception& e )
        {
            spdlog::error( "Deserialization error: {}", e.what() );
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
