system "clear"
require 'colorize'

puts "\n\t**********************************************\n"\
     "\t** define heal signal (any pid) to get root **\n"\
     "\t**********************************************\n\n".bold.white

print "[+] Set signal: ".bold.white
sig = gets.chomp.to_s

heal = "enum {\n"\
       "\trootme = #{sig}\n"\
       "};"

file = File.write("heal.h", heal)
puts "\t[+] Writed!".bold.green
