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
 * Protocol 2 : Simplex Sender protocol which does not receive frames
 * 
 * @author 64932 (Put here your student number)
 */
public class Simplex_snd extends Base_Protocol implements Callbacks {

    public Simplex_snd(Simulator _sim, NetworkLayer _net) {
        super(_sim, _net);      // Calls the constructor of Base_Protocol
        next_frame_to_send = 0;
        // ...
    }

    /**
     * Send a data frame with the data and sequence number received
     * @param seq sequence number
     * @param packet packet data to transmit
     */
    private void send_data_frame(int seq, String packet) {
        Frame data = Frame.new_Data_Frame(seq, prev_seq(0) /*ack*/, 
                null /*ackvec*/, packet);
        prevFrame = data; // Para retransmissão 
        sim.to_physical_layer(data, false /* do not interrupt an ongoing data transmission*/);
    }

    /**
     * From --- Utopian_snd --- you must adapt it to implement a reliable simple protocol!
     * Fetches the network layer for the next packet and starts it transmission
     */
    private void send_next_data_packet() {
        // We can only send one Data packet at a time
        //   you must wait for an ACK before transmitting another one
        //   otherwise the first packet is lost in the channel
        String packet= net.from_network_layer();
        if (packet != null) {
            
            // The ACK field of the DATA frame is always the sequence number before zero, because no packets will be received
            send_data_frame(next_frame_to_send /*seq*/, packet);
            next_frame_to_send = next_seq(next_frame_to_send);
            // Now, the transmission of next DATA frame occurs after receiveing an ACK ...
            sim.start_data_timer();
        }
    }

    /**
     * CALLBACK FUNCTION: handle the beginning of the simulation event
     * @param time current simulation time
     */
    @Override
    public void start_simulation(long time) {
        sim.Log("\nSimplex Sender Protocol\n\tOnly send data!\n\n");
        // Send the first frame here ...
        send_next_data_packet();
    }

    /**
     * CALLBACK FUNCTION: handle the end of Data frame transmission, start timer
     * @param time current simulation time
     * @param seq  sequence number of the Data frame transmitted
     */
    @Override
    public void handle_Data_end(long time, int seq) {
        // ???
        sim.start_data_timer();
    }
    
    /**
     * CALLBACK FUNCTION: handle the data timer event; retransmit failed frames
     * @param time current simulation time
     */
    @Override
    public void handle_Data_Timer(long time) {
        sim.Log(time + ": Timeout, retransmitting frame " + prevFrame.seq() + "\n");
        // Retransmit the last frame sent
        sim.to_physical_layer(prevFrame, false);
        sim.start_data_timer();
    }
    
    /**
     * CALLBACK FUNCTION: handle the ack timer event; send ACK frame
     * @param time current simulation time
     */
    @Override
    public void handle_ack_Timer(long time) {
        // Must not happen
        sim.Log(time + " ACK Timeout - ignored\n");
    }

    /**
     * CALLBACK FUNCTION: handle the reception of a frame from the physical layer
     * @param time current simulation time
     * @param frame frame received
     */
    @Override
    public void from_physical_layer(long time, Frame frame) {
        //sim.Log("from_physical_layer not implemented\n"); 
        if (frame.kind() == Frame.ACK_FRAME) {
            AckFrameIF aframe = frame;  // Auxiliary variable to access the Ack frame fields.
            sim.Log(time + ": Received ACK for frame " + aframe.ack() + "\n");
            // ...
            // parar o timer
            if(aframe.ack() == prev_seq(next_frame_to_send)){
                sim.cancel_data_timer();
                send_next_data_packet();
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
    private Frame prevFrame;
    
    /**
     * Reference to the simulator (Terminal), to get the configuration and send commands
     */
    //final Simulator sim;  -  Inherited from Base_Protocol
    
    /**
     * Reference to the network layer, to send a receive packets
     */
    //final NetworkLayer net;    -  Inherited from Base_Protocol
    
    /**
     * Sequence number of the next data frame
     */
    private int next_frame_to_send;
    
}
