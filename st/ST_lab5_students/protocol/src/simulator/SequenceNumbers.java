/*
 * Sistemas de Telecomunicacoes 
 *          2024/2025
 */
package simulator;

/**
 * Supporting class with basic functions to handle circular sequence numbers
 * 
 * @author lflb@fct.unl.pt
 */
public class SequenceNumbers {

/******************************************************************************/
// Functions to manage sequence numbers
/******************************************************************************/
    
    /**
     * Return true if c > b >= a circularly; false otherwise
     * @param a - lower bound
     * @param b - test value
     * @param c - upper bound
     * @return true is b is between a and c
     */
    public static boolean between(int a, int b, int c) {
        return ((a<=b)&&(b<c)) || ((c<a)&&(a<=b)) || ((b<c)&&(c<a));
    }

    /**
     * Increment one unit a sequence number wrapping when the maximum sequence 
     * number is reached
     * @param n sequence number
     * @param max_sequence maximum sequence number
     * @return the successor of the sequence number
     */
    public static int next_seq(int n, int max_sequence) {
        return (n + 1) % (max_sequence + 1);
    }

    /**
     * Increment k units to a sequence number wrapping when the maximum sequence 
     *    number is reached
     * @param n sequence number
     * @param k increment
     * @param max_sequence maximum sequence number
     * @return the successor of the sequence number
     */
    public static int add_seq(int n, int k, int max_sequence) {
        return (n + k) % (max_sequence + 1);
    }

    /**
     * Decrement one unit a sequence number wrapping when the maximum sequence 
     * number is reached
     * @param n sequence number
     * @param max_sequence maximum sequence number
     * @return the predecessor of the sequence number
     */
    public static int prev_seq(int n, int max_sequence) {
        return (max_sequence  + n) % (max_sequence + 1);
    }

    /**
     * Subtract k units to a sequence number wrapping when the maximum sequence
     * number is reached
     *
     * @param n sequence number
     * @param k decrement
     * @param max_sequence maximum sequence number
     * @return the subtraction of the sequence number
     */
    public static int subt_seq(int n, int k, int max_sequence) {
        return (n + max_sequence  + 1 - k) % (max_sequence  + 1);
    }

    /**
     * Calculates the difference between two sequence numbers taking into 
     * account the wrapping when the maximum sequence number is reached
     * @param a first sequence number
     * @param b first sequence number
     * @param max_sequence maximum sequence number
     * @return number of numbers between a and b
     */
    public static int diff_seq(int a, int b, int max_sequence) {
        if (b>=a) {
            return b-a;
        }
        else {
            return b+max_sequence+1-a;
        }     
    }    
}
