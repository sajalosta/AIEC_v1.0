//-----------------------------------------------------------------------------
// tb_top - testbench top for snix_sync_fifo
//
// Pattern: the testbench DRIVES PINS ONLY and stays silent. All observation
// is done by fifo_event_monitor (event log). No checking anywhere in here.
//
// One test per simulation run, selected by plusarg:
//     ./Vtb_top +TEST=T3_fill_sixteen > T3_fill_sixteen.log
// The only non-monitor output is the [TST] header and completion status.
//-----------------------------------------------------------------------------
`timescale 1ns/1ps

module tb_top;

    localparam DATA_WIDTH = 32;
    localparam FIFO_DEPTH = 16;

    logic                  clk;
    logic                  rst_n;
    logic                  wr_en;
    logic [DATA_WIDTH-1:0] wr_data;
    logic                  full;
    logic                  rd_en;
    logic [DATA_WIDTH-1:0] rd_data;
    logic                  empty;

    snix_sync_fifo #(.DATA_WIDTH(DATA_WIDTH), .FIFO_DEPTH(FIFO_DEPTH)) dut (.*);
    fifo_event_monitor #(.DATA_WIDTH(DATA_WIDTH), .WINDOW(20)) mon (.*);

    // 100 MHz clock
    initial clk = 1'b0;
    always #5 clk = ~clk;

    //-------------------------------------------------------------------------
    // pin driver tasks (stimulus only)
    //-------------------------------------------------------------------------
    task automatic do_reset(int cycles = 3);
        wr_en = 0; rd_en = 0; wr_data = '0; rst_n = 0;
        repeat (cycles) @(posedge clk);
        rst_n = 1;
        @(posedge clk);
    endtask

    task automatic write_word(logic [DATA_WIDTH-1:0] data);
        wr_en = 1; wr_data = data;
        @(posedge clk);
        wr_en = 0;
    endtask

    task automatic write_burst(int n, logic [DATA_WIDTH-1:0] base);
        wr_en = 1;
        for (int i = 0; i < n; i++) begin
            wr_data = base + i;
            @(posedge clk);
        end
        wr_en = 0;
    endtask

    task automatic read_burst(int n);
        rd_en = 1;
        repeat (n) @(posedge clk);
        rd_en = 0;
        @(posedge clk);  // let last read data settle on rd_data
    endtask

    task automatic simultaneous_wr_rd(int n, logic [DATA_WIDTH-1:0] base);
        wr_en = 1; rd_en = 1;
        for (int i = 0; i < n; i++) begin
            wr_data = base + i;
            @(posedge clk);
        end
        wr_en = 0; rd_en = 0;
        @(posedge clk);
    endtask

    task automatic idle(int cycles);
        wr_en = 0; rd_en = 0;
        repeat (cycles) @(posedge clk);
    endtask

    //-------------------------------------------------------------------------
    // test sequences (stimulus per test plan v0.2 - no observation, no checks)
    //-------------------------------------------------------------------------
    string testname;

    // time-zero pin initialization: all DUT inputs driven to safe values
    // before the first clock edge (reset asserted, enables low, data zero)
    initial begin
        rst_n   = 1'b0;
        wr_en   = 1'b0;
        rd_en   = 1'b0;
        wr_data = '0;
    end

    initial begin
        if (!$value$plusargs("TEST=%s", testname))
            testname = "T1_cold_start";
        $display("[TST] test=%s dut=snix_sync_fifo data_width=%0d fifo_depth=%0d",
                 testname, DATA_WIDTH, FIFO_DEPTH);

        case (testname)
            "T1_cold_start": begin
                do_reset(3);
                idle(2);
            end

            "T2_one_in_one_out": begin
                do_reset();
                write_word(32'hA5A50001);
                idle(1);
                read_burst(1);
                idle(2);
            end

            "T3_fill_sixteen": begin
                do_reset();
                write_burst(16, 0);
                idle(2);
            end

            "T4_seventeenth_write": begin
                do_reset();
                write_burst(16, 0);
                idle(1);
                write_word(32'hDEADBEEF);   // attempted while full
                idle(1);
                read_burst(16);
                idle(2);
            end

            "T5_full_drain": begin
                do_reset();
                write_burst(16, 0);
                idle(1);
                read_burst(16);
                idle(2);
            end

            "T6_read_on_dry": begin
                do_reset();
                rd_en = 1;                  // 3 blocked read attempts
                repeat (3) @(posedge clk);
                rd_en = 0;
                idle(1);
                write_word(32'h00000077);
                idle(1);
                read_burst(1);
                idle(2);
            end

            "T7_lap_the_buffer": begin
                do_reset();
                write_burst(16, 0);
                idle(1);
                read_burst(16);
                idle(1);
                write_burst(8, 32'h1000);
                idle(1);
                read_burst(8);
                idle(2);
            end

            "T8_push_pull_together": begin
                do_reset();
                write_burst(8, 0);          // preload values 0..7
                idle(1);
                simultaneous_wr_rd(4, 32'h2000);
                idle(1);
                read_burst(8);              // drain remaining
                idle(2);
            end

            "T9_four_beat_burst": begin
                do_reset();
                write_burst(4, 32'hB0);
                idle(2);
                read_burst(4);
                idle(2);
            end

            default: begin
                $display("[TST] test=%s status=unknown_test", testname);
                $finish;
            end
        endcase

        $display("[TST] test=%s status=completed", testname);
        $finish;
    end

    // safety timeout: a hung test still produces a judgeable log (rule R11)
    initial begin
        #20000;
        $display("[TST] test=%s status=timeout", testname);
        $finish;
    end

endmodule
