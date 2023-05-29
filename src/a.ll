; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [6 x i8] c": %d\0A\00", align 1
@gl = internal global i32 2
@1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@2 = private unnamed_addr constant [7 x i8] c"A: %d\0A\00", align 1
@3 = private unnamed_addr constant [23 x i8] c"--Hello world! %.1lf!\0A\00", align 1
@4 = private unnamed_addr constant [10 x i8] c"! i = %d\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @printi(i32 %0) {
entry:
  %v = alloca i32, align 4
  store i32 %0, i32* %v, align 4
  %v1 = load i32, i32* %v, align 4
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @0, i32 0, i32 0), i32 %v1)
  ret void
}

define i32 @main() {
entry:
  %arr = alloca [3 x [12 x i32]], align 4
  %a = alloca i32, align 4
  store i32 10, i32* %a, align 4
  %a1 = load i32, i32* %a, align 4
  %0 = add i32 %a1, 2
  %b = alloca i32, align 4
  store i32 %0, i32* %b, align 4
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i32* %a)
  %a2 = load i32, i32* %a, align 4
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @2, i32 0, i32 0), i32 %a2)
  %f = alloca double, align 8
  store double 1.000000e-01, double* %f, align 8
  store i32 5, i32* @gl, align 4
  %3 = load i32, i32* @gl, align 4
  %a3 = load i32, i32* %a, align 4
  %4 = add i32 %a3, 1
  %b4 = load i32, i32* %b, align 4
  %5 = add i32 %4, %b4
  %f5 = load double, double* %f, align 8
  %6 = sitofp i32 %5 to double
  %7 = fadd double %6, %f5
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @3, i32 0, i32 2), double %7)
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  br label %cond

cond:                                             ; preds = %inst, %entry
  %i6 = load i32, i32* %i, align 4
  %9 = sitofp i32 %i6 to double
  %10 = fcmp ole double %9, 1.000000e+01
  br i1 %10, label %body, label %end14

body:                                             ; preds = %cond
  %11 = bitcast [3 x [12 x i32]]* %arr to [12 x i32]*
  %12 = getelementptr [12 x i32], [12 x i32]* %11, i32 1
  %13 = bitcast [12 x i32]* %12 to i32*
  %i7 = load i32, i32* %i, align 4
  %14 = getelementptr i32, i32* %13, i32 %i7
  %i8 = load i32, i32* %i, align 4
  store i32 %i8, i32* %14, align 4
  %15 = load i32, i32* %14, align 4
  %i9 = load i32, i32* %i, align 4
  %16 = icmp eq i32 %i9, 5
  br i1 %16, label %then, label %else

then:                                             ; preds = %body
  %17 = bitcast [3 x [12 x i32]]* %arr to [12 x i32]*
  %18 = getelementptr [12 x i32], [12 x i32]* %17, i32 1
  %19 = bitcast [12 x i32]* %18 to i32*
  %i10 = load i32, i32* %i, align 4
  %20 = getelementptr i32, i32* %19, i32 %i10
  %21 = load i32, i32* %20, align 4
  %gl = load i32, i32* @gl, align 4
  %22 = mul i32 %21, %gl
  %f11 = load double, double* %f, align 8
  %23 = sitofp i32 %22 to double
  %24 = fadd double %23, %f11
  %25 = fptosi double %24 to i32
  call void @printi(i32 %25)
  br label %end

else:                                             ; preds = %body
  %i12 = load i32, i32* %i, align 4
  %26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @4, i32 0, i32 0), i32 %i12)
  br label %end

end:                                              ; preds = %else, %then
  br label %inst

inst:                                             ; preds = %end
  %i13 = load i32, i32* %i, align 4
  %27 = add i32 %i13, 1
  store i32 %27, i32* %i, align 4
  %28 = load i32, i32* %i, align 4
  br label %cond

end14:                                            ; preds = %cond
  ret i32 0
}
