#Chelsie Cash
#creative commons license
#feel free to use this however you want

def make_bezier(xys):
    # xys should be a sequence of 2-tuples (Bezier control points)
    n=len(xys)
    combinations=pascal_row(n-1)
    def bezier(ts):
        # This uses basic general formula for bezier curves
        # http://en.wikipedia.org/wiki/B%C3%A9zier_curve#Generalization
        result=[]
        for t in ts:
            tpowers=(t**i for i in range(n))
            upowers=reversed([(1-t)**i for i in range(n)])
            coefs=[c*a*b for c,a,b in zip(combinations,tpowers,upowers)]
            result.append(
                tuple(sum([coef*p for coef,p in zip(coefs,ps)]) for ps in zip(*xys)))
        return result
    return bezier

def pascal_row(n):
    # This returns the nth row of Pascal's Triangle
    result=[1]
    x,numerator=1,n
    for denominator in range(1,n//2+1):
        # print(numerator,denominator,x)
        x*=numerator
        x/=denominator
        result.append(x)
        numerator-=1
    if n&1==0:
        # n is even
        result.extend(reversed(result[:-1]))
    else:
        result.extend(reversed(result)) 
    return result
	
from PIL import Image , ImageDraw
	
if __name__=='__main__':
	im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
	draw = ImageDraw.Draw(im)
	ts=[t/100.0 for t in range(101)]

	xys=[(0,100),(25,50),(50,0)]
	bezier=make_bezier(xys)
	points=bezier(ts)

	xys=[(50,0),(75,50),(100,100)]
	bezier=make_bezier(xys)
	points.extend(bezier(ts))

	xys=[(100,100),(85,75),(75,50)]
	bezier=make_bezier(xys)
	points.extend(bezier(ts))

	xys=[(75,50),(50,50),(25,50)]
	bezier=make_bezier(xys)
	points.extend(bezier(ts))
	
draw.polygon(points,fill=None,outline='red')
im.save('LetterA.png')

#letter B

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(0,0),(0,50),(0,100)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(0,100),(100,100),(0,50)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterB.png')

#letter C

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(100,0),(0,0),(0,80),(100,80)]
bezier=make_bezier(xys)
points=bezier(ts)

draw.polygon(points,fill=None,outline='red')
im.save('LetterC.png')

#letter D

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(10,90),(80,20),(40,30),(10,10)]
bezier=make_bezier(xys)
points=bezier(ts)

draw.polygon(points,fill=None,outline='red')
im.save('LetterD.png')

#letter E

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(80,60),(0,100),(0,20),(60,20)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(24,67)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterE.png')

#letter H

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(0,0),(0,50),(0,100)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(60,100),(40,50),(50,60),(9,60)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterH.png')

#letter I

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(50,20),(50,50),(50,80)]
bezier=make_bezier(xys)
points=bezier(ts)

draw.polygon(points,fill=None,outline='red')
im.save('LetterI.png')

#letter J

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(15,60),(30,85),(50,60)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(50,20),(50,50),(50,60)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterJ.png')

#letter K

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(10,20),(15,50),(15,90)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(80,82),(40,40),(0,80),(0,43),(80,15)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill='red',outline='red')
im.save('LetterK.png')

#letter L

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(15,80),(15,50),(15,20)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(50,80)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterL.png')

#letter M

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(10,80),(25,0),(50,80)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(50,80),(75,0),(100,80)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

xys=[(0,50),(0,30)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterM.png')

#letter N

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(10,72),(25,0),(50,72)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(10,50),(10,30)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterN1.png')

#letter O

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(70,20),(10,25),(30,50),(0,80),(90,69),(82,57),(80,52),(84,49),(86,51)]
bezier=make_bezier(xys)
points=bezier(ts)

draw.polygon(points,fill=None,outline='red')
im.save('LetterO.png')

#letter P

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(40,60),(100,20),(30,30),(40,20)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(40,60),(40,65),(40,100)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterP.png')

#letter Q

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(81,30),(80,25),(70,20),(10,25),(30,50),(0,80),(90,69),(82,57),(80,52),(84,49),(86,51)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(85,100)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterQ.png')

#letter R

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(40,60),(100,20),(30,30),(40,20)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(40,60),(40,65),(40,100)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

xys=[(40,100),(40,60),(90,100)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterR.png')

#letter T

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(50,80),(50,50),(50,20)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(50,80),(49,20)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

xys=[(49,20),(20,20)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

xys=[(49,20),(80,20)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterT.png')

#letter U

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(10,20),(50,100),(70,20)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(48,58),(45,60),(38,58)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill='red',outline='red')
im.save('LetterU.png')

#Letter V

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(10,20),(50,100),(70,20)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(54,57),(45,79),(31,57)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterV.png')

#letter W

im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
draw = ImageDraw.Draw(im)
ts=[t/100.0 for t in range(101)]

xys=[(10,20),(25,100),(50,20)]
bezier=make_bezier(xys)
points=bezier(ts)

xys=[(50,20),(75,100),(100,20)]
bezier=make_bezier(xys)
points.extend(bezier(ts))

draw.polygon(points,fill=None,outline='red')
im.save('LetterW.png')

#im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
#draw = ImageDraw.Draw(im)
#ts=[t/100.0 for t in range(101)]

#xys=[(0,0),(0,50),(0,90)]
#bezier=make_bezier(xys)
#points=bezier(ts)

#xys=[(50,80),(25,10),(0,80)]
#bezier=make_bezier(xys)
#points.extend(bezier(ts))

#draw.polygon(points,fill=None,outline='red')
#im.save('LetterB1.png')


#im = Image.new('RGBA', (100, 100), (0, 0, 0, 0)) 
#draw = ImageDraw.Draw(im)
#s=[t/100.0 for t in range(101)]

#xys=[(10,80),(45,0),(90,80)]
#bezier=make_bezier(xys)
#points=bezier(ts)

#xys=[(37,57),(20,79),(12,57)]
#bezier=make_bezier(xys)
#points.extend(bezier(ts))

#xys=[(50,80),(75,0),(100,80)]
#bezier=make_bezier(xys)
#points.extend(bezier(ts))

#draw.polygon(points,fill=None,outline='red')
#im.save('LetterN.png')