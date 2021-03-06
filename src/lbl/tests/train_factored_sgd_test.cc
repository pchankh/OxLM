#include "gtest/gtest.h"

#include "lbl/factored_weights.h"
#include "lbl/model.h"
#include "lbl/model_utils.h"
#include "lbl/tests/sgd_test.h"
#include "utils/constants.h"

namespace oxlm {

TEST_F(FactoredSGDTest, TestTrainFactoredSGD) {
  FactoredLM model(config);
  model.learn();
  config->test_file = "test.en";
  boost::shared_ptr<Vocabulary> vocab = model.getVocab();
  boost::shared_ptr<Corpus> test_corpus = readTestCorpus(config, vocab);
  Real log_likelihood = 0;
  model.evaluate(test_corpus, log_likelihood);
  EXPECT_NEAR(61.6432151, perplexity(log_likelihood, test_corpus->size()), EPS);
}

TEST_F(FactoredSGDTest, TestTrainFactoredNCE) {
  config->noise_samples = 10;
  FactoredLM model(config);
  model.learn();
  config->test_file = "test.en";
  boost::shared_ptr<Vocabulary> vocab = model.getVocab();
  boost::shared_ptr<Corpus> test_corpus = readTestCorpus(config, vocab);
  Real log_likelihood = 0;
  model.evaluate(test_corpus, log_likelihood);
  EXPECT_NEAR(66.0725250, perplexity(log_likelihood, test_corpus->size()), EPS);
}

} // namespace oxlm
