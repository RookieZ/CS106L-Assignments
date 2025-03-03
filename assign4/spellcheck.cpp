#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
  auto spaceIteratorVector = find_all(source.begin(), source.end(), isspace);

  // 完成分词操作，将token存放在tokens中
  auto tokenGenerator = [&source](auto It1, auto It2) {
    return Token{source, It1, It2};
  };
  std::set<Token> tokens;
  std::transform(spaceIteratorVector.begin(), spaceIteratorVector.end() - 1, 
  spaceIteratorVector.begin() + 1, std::inserter(tokens, tokens.end()), tokenGenerator);

  // 去除token中的空格
  auto isBlank = [](Token token) { 
    return token.content.empty();
  };
  std::erase_if(tokens, isBlank);

  return tokens;
}

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv = std::ranges::views;
  // 过滤出misspell的token
  auto isMisspelled = [&dictionary](Token token) {
    return !dictionary.contains(token.content);
  };

  // 将misspell的token转换为结构体Mispelling
  auto transformToMisspelling = [&dictionary](Token token) {
    // 过滤出按照levenshtein算法距离等于1的词汇
    auto distanceEqualsOne = [&token](std::string str) {
      return levenshtein(token.content, str) == 1;
    };

    auto view = dictionary | rv::filter(distanceEqualsOne);
    std::set<std::string> suggestions(view.begin(), view.end());

    return Mispelling{token, suggestions};
  };

  // 过滤掉没有suggestions的元素
  auto noSuggestions = [](Mispelling mispelling) {
    return !mispelling.suggestions.empty();
  };

  auto view = source 
              | rv::filter(isMisspelled) 
              | rv::transform(transformToMisspelling)
              | rv::filter(noSuggestions);
  std::set<Mispelling> mispellings(view.begin(), view.end());

  return mispellings;
};

/* Helper methods */

#include "utils.cpp"