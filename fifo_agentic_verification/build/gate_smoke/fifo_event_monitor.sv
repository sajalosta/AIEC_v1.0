//-----------------------------------------------------------------------------
// fifo_event_monitor - passive, observation-only, black-box port monitor
//
// Event = any change on any pin or flag (wr_en, wr_data, rd_en, rd_data,
// full, empty, rst_n), timestamped with sim time and cycle number.
// Events are buffered and emitted as a window block every WINDOW (20) cycles.
// Contains no expected values and renders no judgment.
//-----------------------------------------------------------------------------
`timescale 1ns/1ps

module fifo_event_monitor #(
    parameter DATA_WIDTH = 32,
    parameter WINDOW     = 20
)(
    input logic                  clk,
    input logic                  rst_n,
    input logic                  wr_en,
    input logic [DATA_WIDTH-1:0] wr_data,
    input logic                  full,
    input logic                  rd_en,
    input logic [DATA_WIDTH-1:0] rd_data,
    input logic                  empty
);

    int unsigned cycle;
    int unsigned win_start;
    string       evq[$];
    bit          primed;

    logic                  p_rst_n, p_wr_en, p_rd_en, p_full, p_empty;
    logic [DATA_WIDTH-1:0] p_wr_data, p_rd_data;

    function automatic void ev(string s);
        evq.push_back(s);
    endfunction

    task automatic flush_window();
        $display("[WIN] cycles=%0d..%0d events=%0d", win_start, cycle, evq.size());
        foreach (evq[i]) $display("%s", evq[i]);
        evq.delete();
        win_start = cycle + 1;
    endtask

    always_ff @(posedge clk) begin
        if (primed) begin
            if (rst_n   !== p_rst_n)
                ev($sformatf("[EVT] t=%0t cycle=%0d pin=rst_n   %0d -> %0d", $time, cycle, p_rst_n, rst_n));
            if (wr_en   !== p_wr_en)
                ev($sformatf("[EVT] t=%0t cycle=%0d pin=wr_en   %0d -> %0d", $time, cycle, p_wr_en, wr_en));
            if (wr_data !== p_wr_data)
                ev($sformatf("[EVT] t=%0t cycle=%0d pin=wr_data 0x%08h -> 0x%08h", $time, cycle, p_wr_data, wr_data));
            if (rd_en   !== p_rd_en)
                ev($sformatf("[EVT] t=%0t cycle=%0d pin=rd_en   %0d -> %0d", $time, cycle, p_rd_en, rd_en));
            if (rd_data !== p_rd_data)
                ev($sformatf("[EVT] t=%0t cycle=%0d pin=rd_data 0x%08h -> 0x%08h", $time, cycle, p_rd_data, rd_data));
            if (full    !== p_full)
                ev($sformatf("[EVT] t=%0t cycle=%0d flag=full  %0d -> %0d", $time, cycle, p_full, full));
            if (empty   !== p_empty)
                ev($sformatf("[EVT] t=%0t cycle=%0d flag=empty %0d -> %0d", $time, cycle, p_empty, empty));
        end

        p_rst_n   <= rst_n;
        p_wr_en   <= wr_en;
        p_wr_data <= wr_data;
        p_rd_en   <= rd_en;
        p_rd_data <= rd_data;
        p_full    <= full;
        p_empty   <= empty;
        primed    <= 1'b1;

        if (primed && ((cycle + 1) % WINDOW == 0))
            flush_window();

        cycle <= cycle + 1;
    end

    // emit any remaining buffered events at end of simulation
    final begin
        if (evq.size() > 0) begin
            $display("[WIN] cycles=%0d..%0d events=%0d (final)", win_start, cycle, evq.size());
            foreach (evq[i]) $display("%s", evq[i]);
        end
        $display("[MON] total_cycles=%0d", cycle);
    end

endmodule
