/*
 * Sistemas de Telecomunicacoes 
 *          2024/2025
 */
package simulator;


/**
 * Defines the frames exchanged between the terminal protocol objects and the 
 * channel. Implements methods to read the frame fields' contents.
 * 
 * @author lflb@fct.unl.pt
 */
public interface DataFrameIF {
        
    /* Methods to read the frame fields' contents */
        
    /**
     * Get the kind of the frame object
     * @return the kind of the frame
     */
    public int kind();
    
    /**
     * Get the sequence number (valid for DATA_FRAME kind)
     * @return the sequence number
     */
    public int seq();

    /**
     * Get the acknowledgement number
     * @return the acknowledgement number
     */
    public int ack();

    /**
     * Get the acknowledgement vector field
     * @return the acknowledgement vector
     */
    public int[] ackvec();

    /**
     * Get the information of a DATA_FRAME
     * @return the information carried
     */
    public String info();
        
}
