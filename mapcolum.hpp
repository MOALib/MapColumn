#include <map>
#include <string>
#include <unordered_map>

/**
 * @file mapcolum.hpp
 * @brief Wide-column store with C++11 and maps
 * @copyright MIT License
 */

#ifndef MXPSQL_MAPCOLUM_HPP
#define MXPSQL_MAPCOLUM_HPP

#if (defined(__cplusplus) && (__cplusplus <= 199711L && !(__cplusplus >= 201103L)))  || (defined(_MSC_VER) && _MSC_VER >= 1900)
  #error This library needs at least a C++11 compliant compiler
#endif

namespace MXPSQL{
  /**
   * @namespace MXPSQL::MapColumn
   * @brief Namespace, for the types
   * Contains utility function and types, like conversion between types and getting a "row" ( the child map ) from a "column" ( the parent map )
   */
  namespace MapColumn {
    /**
     * @brief Alias for std::map<std::string, whatever>
     * 
     * @tparam t the type
     */
    template<typename t>
    using dictionary = std::map<std::string, t>;

    /**
     * @brief Like dictionary but unordered
     * @see dictionary
     * @tparam t the type
     */
    template<typename t>
    using unordered_dictionary = std::unordered_map<std::string, t>;

    /** 
     * @brief A very simple wide column store implemented an alias of std::map in C++11: dictionary
     * @tparam T The type of the values
     * @see unordered_map_column
     * @see dictionary
     * A very simple type, std::map implementation
     */ 
    template<typename t>
    using map_column = dictionary<dictionary<t>>;

    /**
     * @brief an unordered version of map_column
     * @tparam T The type of the values
     * @see map_column
     * @see unordered_dictionary
     * An unordered version of map_column
     */
    template<typename t>
    using unordered_map_column = unordered_dictionary<unordered_dictionary<t>>;


    /** 
     * @brief converts a map_column to an unordered_map_column
     * @tparam T The type of the values
     * @param map_column The map_column to convert
     * @return The unordered_map_column
     * @see map_column
     * @see unordered_map_column
     */ 
    template<typename t>
    unordered_map_column<t> ordered_to_unordered_map_column(map_column<t>& map_column){
        unordered_map_column<t> unordered_map_column;
        for(auto pair : map_column){
          std::unordered_map<std::string, t> unordered_map_column_map;

          for(auto pair2 : pair.second){
            unordered_map_column_map[pair2.first] = pair2.second;
          }

          unordered_map_column[pair.first] = unordered_map_column_map;
        }
        return unordered_map_column;
    }

    /** 
     * @brief converts an unordered_map_column to a map_column
     * @tparam T The type of the values
     * @param unordered_map_column The unordered_map_column to convert
     * @return The map_column
     * @see map_column
     * @see unordered_map_column
     */ 
    template<typename t>
    map_column<t> unordered_to_ordered_map_column(unordered_map_column<t>& unordered_map_column){
        map_column<t> map_column;
        for(auto pair : unordered_map_column){
          std::map<std::string, t> map_column_map;

          for(auto pair2 : pair.second){
            map_column_map[pair2.first] = pair2.second;
          }

          map_column[pair.first] = map_column_map;
        }
        return map_column;
    }

    /**
     * @brief Get the row object
     * @see map_column
     * @see dictionary
     * @tparam t the type
     * @param map_column the wide column store
     * @param column_name the name of the column
     * @return dictionary<t> the row
     */
    template<typename t>
    dictionary<t> get_row_ordered(map_column<t>& map_column, std::string column_name){
      return map_column[column_name];
    }

    /**
     * @brief Like get_row_ordered but for unordered_map_column
     * @see unordered_map_column
     * @see unordered_dictionary
     * @tparam t the type
     * @param unordered_map_column the wide column store
     * @param column_name the name of the column
     * @return unordered_dictionary<t> the row
     */
    template<typename t>
    unordered_dictionary<t> get_row_unordered(unordered_map_column<t>& unordered_map_column, std::string column_name){
      return unordered_map_column[column_name];
    }
  }
}

#endif