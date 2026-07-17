//-----------------------------------------------------------------------------
// snix_sync_fifo - synchronous FIFO, registered read port
//-----------------------------------------------------------------------------
module snix_sync_fifo #(
    parameter DATA_WIDTH = 32,
    parameter FIFO_DEPTH = 16   // must be power of 2
)(
    input  logic                   clk,
    input  logic                   rst_n,
    input  logic                   wr_en,
    input  logic [DATA_WIDTH-1:0]  wr_data,
    output logic                   full,
    input  logic                   rd_en,
    output logic [DATA_WIDTH-1:0]  rd_data,
    output logic                   empty
);

    localparam PTR_WIDTH = $clog2(FIFO_DEPTH) + 1;

    logic [DATA_WIDTH-1:0] mem [0:FIFO_DEPTH-1];
    logic [PTR_WIDTH-1:0]  wr_ptr, rd_ptr;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            wr_ptr <= '0;
        else if (wr_en && !full) begin
            mem[wr_ptr[PTR_WIDTH-2:0]] <= wr_data;
            wr_ptr <= wr_ptr + 1;
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rd_ptr  <= '0;
            rd_data <= '0;
        end
        else if (rd_en && !empty) begin
            rd_ptr  <= rd_ptr + 1;
            rd_data <= mem[rd_ptr[PTR_WIDTH-2:0]];
        end
    end

    assign empty = (wr_ptr == rd_ptr);
    assign full  = (wr_ptr[PTR_WIDTH-1]   != rd_ptr[PTR_WIDTH-1]) &&
                   (wr_ptr[PTR_WIDTH-2:0] == rd_ptr[PTR_WIDTH-2:0]);

endmodule
