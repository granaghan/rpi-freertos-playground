library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.numeric_std.all;
--  A testbench has no ports.
entity MAX31855_tb is
end entity MAX31855_tb;

architecture Behav of MAX31855_tb is
   component MAX31855 is

      port
      (
         clk      : in  std_logic;
         cs_n     : in  std_logic;
         data_out : out std_logic
      );
   end component MAX31855;

   for MAX318550: MAX31855 use entity work.MAX31855;
   signal clk       : std_logic := '0';
   signal cs_n      : std_logic := '1';
   signal data_out  : std_logic := 'Z';

begin
   --  Component instantiation.
   MAX318550: MAX31855
   port map
   (
      clk      => clk,
      cs_n     => cs_n,
      data_out => data_out
   );

   process_MAX31855_tb : process
   variable i : natural := 0;
   begin
      wait for 1 ns;
      cs_n <= '0';

      wait for 1 ns;
      wait for 1 ns;
      wait for 1 ns;
      wait for 1 ns;
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      clk <= '1';
      wait for 1 ns;

      clk <= '0';
      wait for 1 ns;

      wait;
   end process process_MAX31855_tb;


end architecture Behav;