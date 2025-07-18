/*
 * Sistemas de Telecomunicacoes 
 *          2024/2025
 */
package protocol;

import terminal.Simulator;
import simulator.Frame;
import simulator.SequenceNumbers;
import terminal.NetworkLayer;

/**
 * Base protocol class that defines support functions for a basic timer interface,
 *     manipulating sequence numbers and default event handlers
 * 
 * @author lflb@fct.unl.pt
 */
public class Base_Protocol implements Callbacks {

    /**
     * Generic constructor for a protocol
     * @param _sim  simulator object
     * @param _net  network layer object
     */
    public Base_Protocol(Simulator _sim, NetworkLayer _net) {
        this.sim = _sim;
        this.net = _net;
    }

    
/******************************************************************************/
// Code to manage sequence numbers
//    Uses the static functions from SequenceNumbers class 
/******************************************************************************/
    
    /**
     * Return true if c > b >= a circularly, false otherwise
     * @param a - lower bound
     * @param b - test value
     * @param c - upper bound
     * @return true is b is between a and c
     */
    static boolean between(int a, int b, int c) {
        return SequenceNumbers.between(a,b,c);
    }

    /**
     * Increment one unit a sequence number wrapping when the maximum sequence 
     * number is reached
     * @param n sequence number
     * @return the successor of the sequence number
     */
    final int next_seq(int n) {
        return SequenceNumbers.next_seq(n, sim.get_max_sequence());
    }

    /**
     * Increment k units to a sequence number wrapping when the maximum sequence 
     *    number is reached
     * @param n sequence number
     * @param k increment
     * @return the successor of the sequence number
     */
    final int add_seq(int n, int k) {
        return SequenceNumbers.add_seq(n, k, sim.get_max_sequence());
    }

    /**
     * Decrement one unit a sequence number wrapping when the maximum sequence 
     * number is reached
     * @param n sequence number
     * @return the predecessor of the sequence number
     */
    final int prev_seq(int n) {
        return SequenceNumbers.prev_seq(n, sim.get_max_sequence());
    }

    /**
     * Subtract k units to a sequence number wrapping when the maximum sequence
     * number is reached
     *
     * @param n sequence number
     * @param k decrement
     * @return the subtraction of the sequence number
     */
    final int subt_seq(int n, int k) {
        return SequenceNumbers.subt_seq(n, k, sim.get_max_sequence());
    }

    /**
     * Calculates the difference between two sequence numbers taking into 
     * account the wrapping when the maximum sequence number is reached
     * @param a first sequence number
     * @param b first sequence number
     * @return number of numbers between a and b
     */
    int diff_seq(int a, int b) {
        return SequenceNumbers.diff_seq(a, b, sim.get_max_sequence());
    }

    
/******************************************************************************/
// Code that defines default event handlers
/******************************************************************************/
        
    /**
     * Default implementation for start_simulation event
     * @param time  current simulation time
     */
    @Override
    public void start_simulation(long time) {
        sim.Log(time+" Base_Protocol.start_simulation() ignored\n");
    }

    /**
     * Default implementation for handle_Data_end event
     * @param time  current simulation time
     * @param seq   data sequence number
     */
    @Override
    public void handle_Data_end(long time, int seq) {
        sim.Log(time+" Base_Protocol.Data_end("+seq+") ignored\n");
    }

    /**
     * Default implementation for handle_Data_Timer event
     * @param time  current simulation time
     */
    @Override
    public void handle_Data_Timer(long time) {
        sim.Log(time+" Base_Protocol.data_Timeout() ignored\n");
    }

    /**
     * Default implementation for handle_ack_Timer event
     * @param time  current simulation time
     */
    @Override
    public void handle_ack_Timer(long time) {
        sim.Log(time+" Base_Protocol.ack_Timer ignored\n");
    }

    /**
     * Default implementation for from_physical_layer event
     * @param time  current simulation time
     * @param frame frame received
     */
    @Override
    public void from_physical_layer(long time, Frame frame) {
        sim.Log(time+" Base_Protocol.from_physical_layer("+frame+") ignored\n");
    }
    
    /**
     * Default implementation for end_simulation event
     * @param time  current simulation time
     */
    @Override
    public void end_simulation(long time) {
        sim.Log(time+" Base_Protocol.end_simulation ignored\n");
    }
    

    
    /* Variables */
    
    /**
     * Reference to the simulator (Terminal), to get the configuration and send commands
     */
    final Simulator sim;
    
    /**
     * Reference to the network layer, to send a receive packets
     */
    final NetworkLayer net;
    
}
