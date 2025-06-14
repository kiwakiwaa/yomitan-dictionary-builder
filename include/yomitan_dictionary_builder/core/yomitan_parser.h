#ifndef YOMITAN_PARSER_H
#define YOMITAN_PARSER_H

#include "yomitan_dictionary_builder/core/dictionary/yomitan_dictionary.h"
#include "yomitan_dictionary_builder/config/parser_config.h"
#include "yomitan_dictionary_builder/core/xml_parser.h"
#include "yomitan_dictionary_builder/utils/file_utils.h"

class YomitanParser : public XMLParser
{
public:
    explicit YomitanParser(std::unique_ptr<YomitanDictionary> dictionary, const ParserConfig& parserConfig);

    ~YomitanParser() override;

    /**
     * Parse a single dictionary entry
     * @param term The term
     * @param reading The reading of the term
     * @param doc The XML document containing the dictionary entry
     * @param infoTag Optional info tag
     * @param posTag Optional part-of-speech tag
     * @param searchRank Optional search rank
     * @param sequenceNumber Optional sequence number
     * @param ignoreExpressions
     * @return true if parsing was successful
     */
    [[nodiscard]] bool parseEntry(
        const std::string& term,
        const std::string& reading,
        const pugi::xml_document& doc,
        const std::optional<std::string>& infoTag = std::nullopt,
        const std::optional<std::string>& posTag = std::nullopt,
        std::optional<int> searchRank = std::nullopt,
        std::optional<long> sequenceNumber = std::nullopt,
        std::optional<bool> ignoreExpressions = std::nullopt
    ) const;


    /**
     * Export the dictionary to the specified path
     * @param outputPath Path to export the dictionary to
     * @return true if export was successful
     */
    [[nodiscard]] bool exportDictionary(std::string_view outputPath) const;

protected:

    /**
     * Get part-of-speech tags for a term
     * @param term Term to get tags for
     * @return Pair of info tag and part-of-speech tag
     */
    std::pair<std::string, std::string> getPartOfSpeechTags(std::string_view term);

private:

    std::unique_ptr<YomitanDictionary> dictionary;
};


#endif