# Machine Learning in Hottspot Capital

## Plan
-[x] Define Machine Learning / AI
  * AI -> Machine Learning -> Deep Learning
    * Deep Learning is basically ML using multilayered neural networks. The
      network models self-learn to improve the models ability to conduct a
      task.
  * Using computers to mimic human learning to complete tasks
  * The tasks usually fall in one of a few categories:
    1. Prediction
    2. Classifcation / Categorization / Grouping / Clustering

-[ ] Figure out what machine learning algorithms are applicable for predicting
future price
  * Neural Networks seem most applicable. So far the most applicable-seeming
    models are:
    * Long Short Term Memory (LSTM) Networks
      * Maybe feed this into a Recurrent Neural Network (RNN)
    * Radial Basis Function Neural Networks

-[ ] Seek or custom build implementations of said algorithm(s)

## LSTM Notes
* Its key application is to make time series predictions based on prior information.
* Is best paired with Recurrent Neural Network (RNN)
* RNN consists of a node. The node receives an input, executes a computation,
  and returns an output.
* It repeats this step by returning the output to the node as a secondary input
  to a new input.
  * This constrasts to Feed Forward Neural Networks (FFNN) which only pass
    inputs through successive hidden layers before returning an output.
  * They don't send the output back through the hidden layers as inputs.
* RNN, however, suffers from the **Long-Term Dependency Problem**:
  * Over time, as more data is stored in the node, it becomes less effective at
    learning.
* LSTM resolves the Long-Term Dependency Problem by storing state in the node
  inside of an LSTM `cell`.
* This LSTM cell persists three bits of information in three separate gates:
  1. Forget Gate - What prior data (inputs and returned outputs) can be forgotten?
  2. Input  Gate - What new info should be added to the LSTM cell?
  3. Output Gate - What data should be output from the cell?
* Each LSTM cell gate maintains a value within a binary range (0 - 1) that
  indicates how much data should pass through it.

## Education Resources
* [Top 10 Machine Learning Algorithms For Beginners: Supervised, and
  More](https://www.simplilearn.com/10-algorithms-machine-learning-engineers-need-to-know-article)
* [Top 10 Deep Learning Algorithms You Should Know in
  2023](https://www.simplilearn.com/tutorials/deep-learning-tutorial/deep-learning-algorithm)
* [Deep Learning Specialization](https://bit.ly/443s7DE)
* [clstm](https://github.com/tmbdev/clstm)
* [lstm-rnn](https://github.com/lephong/lstm-rnn)
