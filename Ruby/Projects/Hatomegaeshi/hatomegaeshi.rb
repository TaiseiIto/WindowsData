# -*- coding: utf-8 -*-
require 'Matrix'
class Polygon
  def initialize(points)
    @points = points
  end

  # 回転
  def rotate(n)
    rad = ( n * Math::PI/ 180.0 )
    rotate_matrix = Matrix[
      [Math.cos(rad), -Math.sin(rad), 0],
      [Math.sin(rad), Math.cos(rad), 0],
      [0, 0, 1]
    ]
    rotated = []
    @points.each do |point|
      vector = rotate_matrix * Vector[point[:x], point[:y], 1]
      rotated << { x: vector[0], y: vector[1] }
    end
    return Polygon.new(rotated)
  end

  # 移動
  def transfer(x, y)
    transfer_matrix = Matrix[[1, 0, x], [0, 1, y], [0, 0, 1]]
    transfered = []
    @points.each do |point|
      vector = transfer_matrix * Vector[point[:x], point[:y], 1]
      transfered << { x: vector[0], y: vector[1] }
    end
    return Polygon.new(transfered)
  end

  def array
  	Array.new(@points)
  end
end




puts "四角形の座標を入力してください"
print "点A x:"
point_A_x = gets.chomp.to_f
print "    y:"
point_A_y = gets.chomp.to_f
print "点B x:"
point_B_x = gets.chomp.to_f
print "    y:"
point_B_y = gets.chomp.to_f
print "点C x:"
point_C_x = gets.chomp.to_f
print "    y:"
point_C_y = gets.chomp.to_f
print "点D x:"
point_D_x = gets.chomp.to_f
print "    y:"
point_D_y = gets.chomp.to_f

#それぞれの中点
midpoint_AB_x = (point_A_x + point_B_x)/(2.to_f)
midpoint_AB_y = (point_A_y + point_B_y)/(2.to_f)
midpoint_BC_x = (point_B_x + point_C_x)/(2.to_f)
midpoint_BC_y = (point_B_y + point_C_y)/(2.to_f)
midpoint_CD_x = (point_C_x + point_D_x)/(2.to_f)
midpoint_CD_y = (point_C_y + point_D_y)/(2.to_f)
midpoint_DA_x = (point_D_x + point_A_x)/(2.to_f)
midpoint_DA_y = (point_D_y + point_A_y)/(2.to_f)

#点midpoint_ABと点midpoint_CDの直線と点midpoint_BCと点midpoint_DAの直線の交点
#プログラムで求めたいがここでは入力してもらう
puts "直線ABの中点と直線CDの中点の直線と、直線BCの中点と直線DAの中点の直線の交点の座標を入力してください"
print "    x:"
point_O_x = gets.chomp.to_f
print "    y:"
point_O_y = gets.chomp.to_f

square_A = [{ x: point_A_x, y: point_A_y }, { x: midpoint_AB_x, y: midpoint_AB_y }, { x: point_O_x, y: point_O_y }, { x: midpoint_DA_x, y: midpoint_DA_y }]
square_B = [{ x: midpoint_AB_x, y: midpoint_AB_y }, { x: point_B_x, y: point_B_y }, { x: midpoint_BC_x, y: midpoint_BC_y }, { x: point_O_x, y: point_O_y }]

p1 = Polygon.new(square_A)

square_P = p1.transfer((-1)*midpoint_DA_x, (-1)*midpoint_DA_y).rotate(180).transfer(midpoint_DA_x, midpoint_DA_y).array
p2 = Polygon.new(square_B)
square_Q = p2.transfer((-1)*midpoint_BC_x, (-1)*midpoint_BC_y).rotate(180).transfer(midpoint_BC_x, midpoint_BC_y).array

square_DP = [{ x: square_P[2][:x] , y: square_P[2][:y]}, { x: point_O_x , y: point_O_y }, { x: midpoint_CD_x , y: midpoint_CD_y  }, { x: square_P[1][:x] , y: square_P[1][:y] }]



p3 = Polygon.new(square_DP)
square_DP_last = p3.transfer((-1)*midpoint_CD_x, (-1)*midpoint_CD_y).rotate(180).transfer(midpoint_CD_x, midpoint_CD_y).array


square_hatomegaeshi = [{ x: point_O_x , y: point_O_y }, { x: square_Q[3][:x] , y: square_Q[3][:y] }, { x: square_DP_last[0][:x] , y:  square_DP_last[0][:y] }, { x: square_DP_last[1][:x] , y: square_DP_last[1][:y] }]

#デバック用
# puts ""
# puts "square_A:#{square_A}"
# puts "square_B:#{square_B}"
# puts "square_P:#{square_P}"
# puts "square_Q:#{square_Q}"
# puts "square_DP:#{square_DP}"
# puts "square_DP_last:#{square_DP_last}"
# puts "square_hatomegaeshi:#{square_hatomegaeshi}"

puts "はとめがえし後の四角形の座標"
    square_hatomegaeshi.each do |i|
      puts "X: #{i[:x].round(6)}, Y: #{i[:y].round(6)}"
  end
