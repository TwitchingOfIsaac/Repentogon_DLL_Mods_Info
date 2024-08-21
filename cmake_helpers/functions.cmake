function(convert_to_pascal_case input output)
    string(REPLACE " " ";" words_list ${input})
    set(result "")

    foreach(word IN LISTS words_list)
        string(SUBSTRING ${word} 0 1 first_char)
        string(TOUPPER ${first_char} first_char)
        string(SUBSTRING ${word} 1 -1 rest)
        string(TOLOWER ${rest} rest)
        string(APPEND result "${first_char}${rest}")
    endforeach()

    set(${output} "zhl${result}" PARENT_SCOPE)
endfunction()