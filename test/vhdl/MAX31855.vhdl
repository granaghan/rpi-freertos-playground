library IEEE;
use IEEE.numeric_std.all;
use IEEE.STD_LOGIC_1164.ALL;
--use IEEE.STD_LOGIC_ARITH.all;
--use IEEE.STD_LOGIC_UNSIGNED.all;

entity MAX31855 is
   port
   (
      clk      : in  std_logic;
      cs_n     : in  std_logic;
      data_out : out std_logic
   );
end entity MAX31855;

architecture rtl of MAX31855 is
   constant dummy_data: STD_LOGIC_VECTOR(31 downto 0) := x"02300000";
   type state_type is (IDLE, SHIFTING);
   signal state       : state_type := IDLE;
   signal shift_count : natural    := 0;
   signal data        : STD_LOGIC_VECTOR(31 downto 0) := dummy_data;
begin
   process(clk, cs_n)
   begin
      case state is
         when IDLE =>
            if falling_edge(cs_n) then
               state <= SHIFTING;
            end if;
            data_out <= 'Z';
         when SHIFTING =>
            if(rising_edge(clk)) then
               data_out <= data(31);
               data <= data(30 downto 0) & '0';

               if shift_count < 31 then
                  shift_count <= shift_count + 1;
               else
                  shift_count <= 0;
                  data <= dummy_data;
                  state <= IDLE;
               end if;
            end if;
      end case;
   end process;
end rtl;