function ert_make_rtw_hook(hookMethod, ...
                           modelName, ...
                           rtwroot, ...
                           templateMakefile, ...
                           buildOpts, ...
                           buildArgs, ...
                           buildInfo) %#ok<INUSL,INUSD> 
% GRT_MAKE_RTW_HOOK - This is an example GRT hook file for the build
% process (make_rtw).
%
% This hook file (i.e., file that implements various codegen callbacks) is
% called for system target file grt.tlc.  The file leverages
% strategic points of the build process.  A brief synopsis of the callback
% API is as follows:
%
% grt_make_rtw_hook(hookMethod, modelName, rtwroot, templateMakefile,
%                   buildOpts, buildArgs, buildInfo)
%
% hookMethod:
%   Specifies the stage of the build process.  Possible values are
%   entry, before_tlc, after_tlc, before_make, after_make and exit, etc.
%
% modelName:
%   Name of model.  Valid for all stages.
%
% rtwroot:
%   Reserved.
%
% templateMakefile:
%   Name of template makefile.  Valid for stages 'before_make' and 'exit'.
%
% buildOpts:
%   Valid for stages 'before_make' and 'exit', a MATLAB structure
%   containing fields
%
%   modules:
%     Char array specifying list of generated C files: model.c, model_data.c,
%     etc.
%
%   codeFormat:
%     Char array containing code format: 'RealTime', 'RealTimeMalloc',
%     'Embedded-C', and 'S-Function'
%
%   noninlinedSFcns:
%     Cell array specifying list of non-inlined S-Functions.
%
% buildArgs:
%   Char array containing the argument to make_rtw.  When pressing the build
%   button through the Configuration Parameter Dialog, buildArgs is taken
%   verbatim from whatever follows make_rtw in the make command edit field.
%   From MATLAB, it is whatever is passed into make_rtw.  For example, its
%   'optimized_fixed_point=1' for make_rtw('optimized_fixed_point=1').
%
% buildInfo: 
%   An RTW.BuildInfo object containing information for compiling and 
%   linking generated code. Available for the 'after_tlc', 'before_make', 
%   'after_make', and 'exit' stages only.
%
% Copyright 2024 The MathWorks, Inc.
  
  switch hookMethod
   case 'error'
    % Called if an error occurs anywhere during the build.  If no error occurs
    % during the build, then this hook will not be called.  Valid arguments
    % at this stage are hookMethod and modelName. This enables cleaning up
    % any static or global data used by this hook file.
    
   case 'entry'
    % Called at start of code generation process (before anything happens.)
    % Valid arguments at this stage are hookMethod, modelName, and buildArgs.    
    
   case 'before_tlc'
    % Called just prior to invoking TLC Compiler (actual code generation.)
    % Valid arguments at this stage are hookMethod, modelName, and
    % buildArgs
    
   case 'after_tlc'
    % Called just after to invoking TLC Compiler (actual code generation.)
    % Valid arguments at this stage are hookMethod, modelName, and
    % buildArgs
   case 'before_make'
    % Called after code generation is complete, and just prior to kicking
    % off make process (assuming code generation only is not selected.)  All
    % arguments are valid at this stage.
   case 'after_make'
    % Called after make process is complete. All arguments are valid at 
    % this stage.
    
   case 'exit' ; rtwpostbuildcallback()
       
    % Called at the end of the build process.  All arguments are valid
    % at this stage.
    
  end