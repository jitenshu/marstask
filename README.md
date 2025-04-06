# marstask
I genuinely enjoyed working on these tasks. each one felt different — some were quick brain teasers, others made me think more deeply. It never felt boring. even the math-heavy parts turned out to be fun once i got into the flow. I liked that it wasn’t just about writing code — it was about understanding problems, making logical decisions, and thinking like an engineer . Overall, it was a great experience, and it definitely pushed me to learn and think creatively.

Equations and theorems used

1 - sqrt(x * x + y * y + z * z) //for finding distance
2 - converting Euler angles (roll, pitch, yaw) to quaternion form.
    qw = cos(roll/2) * cos(pitch/2) * cos(yaw/2) + sin(roll/2) * sin(pitch/2) * sin(yaw/2)
    qx = sin(roll/2) * cos(pitch/2) * cos(yaw/2) - cos(roll/2) * sin(pitch/2) * sin(yaw/2)
    qy = cos(roll/2) * sin(pitch/2) * cos(yaw/2) + sin(roll/2) * cos(pitch/2) * sin(yaw/2)
    qz = cos(roll/2) * cos(pitch/2) * sin(yaw/2) - sin(roll/2) * sin(pitch/2) * cos(yaw/2)
3-  original_char = encoded_char - position_index //shifting characters backward using position index

challeneges faced

med1-understanding how the rover’s camera being offset affects the actual position was a bit tricky at first.
med2-handling the spacing between letters and words in morse was confusing initially — had to carefully manage single and double spaces.
med3-managing ascii values and making sure it wraps around correctly without breaking was slightly confusing at first.
med5-quaternion math was new to me, and understanding the conversion from euler angles required reading and revisiting trigonometry.
high1-figuring out how to convert the obstacle format from the file into a proper grid took a little thinking.debugging edge cases like blocked paths or boundaries took extra time.

Resources used

mainly - chatgpt and google
