/*
 * Sistemas de Telecomunicacoes 
 *          2024/2025
 */
package protocol;

import simulator.AckFrameIF;
import simulator.DataFrameIF;
import terminal.Simulator;
import simulator.Frame;
import terminal.NetworkLayer;

/**
 * Protocol 2 : Simplex Receiver protocol which does not transmit frames
 * 
 * @author 64932 (Put here your student number)
 */
public class Simplex_rcv extends Base_Protocol implements Callbacks {

    public Simplex_rcv(Simulator _sim, NetworkLayer _net) {
        super(_sim, _net);      // Calls the constructor of Base_Protocol
        frame_expected = 0;
    }

    /**
     * CALLBACK FUNCTION: handle the beginning of the simulation event
     * @param time current simulation time
     */
    @Override
    public void start_simulation(long time) {
        sim.Log("\nSimplex Receiver Protocol\n\tOnly receive data!\n\n");
        //sim.Log("\nNot implemented yet\n\n");
    }

    /**
     * CALLBACK FUNCTION: handle the end of Data frame transmission, start timer
     * @param time current simulation time
     * @param seq  sequence number of the Data frame transmitted
     */
    @Override
    public void handle_Data_end(long time, int seq) {
        sim.Log(time + " Data_end - ignored\n");
    }
    
    /**
     * CALLBACK FUNCTION: handle the Data timer event; retransmit failed frames
     * @param time current simulation time
     */
    @Override
    public void handle_Data_Timer(long time) {
        // Data Timeout
    }
    
    /**
     * CALLBACK FUNCTION: handle the ack timer event; send ACK frame
     * @param time current simulation time
     */
    @Override
    public void handle_ack_Timer(long time) {
        // ACK Timeout
    }

    /**
     * CALLBACK FUNCTION: handle the reception of a frame from the physical layer
     * @param time current simulation time
     * @param frame frame received
     */
    @Override
    public void from_physical_layer(long time, Frame frame) {
        //sim.Log("from_physical_layer not implemented\n");
        /* After receiving the data, you need to send an ACK frame!
        //  Start with the source code from Utopian_rcv:  
        //*/
        if (frame.kind() == Frame.DATA_FRAME) {     // Check the frame kind
            DataFrameIF dframe = frame;  // Auxiliary variable to access the Data frame fields.
            if (dframe.seq() == frame_expected) {    // Check the sequence number
                // Send the frame to the network layer
                sim.Log(time + ": Received DATA frame with seq = " + dframe.seq() + "\n");
                if (net.to_network_layer(dframe.info())) {
                    // Increment the expected sequence number
                    Frame aframe = Frame.new_Ack_Frame(dframe.seq(), null);
                    sim.Log(time + ": Sending ACK for frame " + frame_expected + "\n");
                    sim.to_physical_layer(aframe, false);
                    frame_expected = next_seq(frame_expected);
                }
            }
            else{
                sim.Log(time + ": Unexpected sequence number. Expected " + frame_expected + ", got " + dframe.seq() + "\n");
                Frame aframe = Frame.new_Ack_Frame(prev_seq(frame_expected), null);
                sim.Log(time + ": Re-sending ACK for frame " + prev_seq(frame_expected) + "\n");
                sim.to_physical_layer(aframe, false);
            }
        }
   }

    /**
     * CALLBACK FUNCTION: handle the end of the simulation
     * @param time current simulation time
     */
    @Override
    public void end_simulation(long time) {
        sim.Log("Stopping simulation\n");
    }
    
    
    /* Variables */
    
    /**
     * Reference to the simulator (Terminal), to get the configuration and send commands
     */
    //final Simulator sim;  -  Inherited from Base_Protocol
    
    /**
     * Reference to the network layer, to send a receive packets
     */
    //final NetworkLayer net;    -  Inherited from Base_Protocol
    
    /**
     * Expected sequence number of the next data frame received
     */
    private int frame_expected;
    
}
