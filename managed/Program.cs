using Mono.CSharp;
using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace managed
{
    public class Foo : DynamicObject
    {
        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            result = 500;
            return true;
        }
    }
    public class Program
    {
        static void Main(string[] args)
        {
            var settings = new CompilerSettings();
            var printer = new ConsoleReportPrinter();
            var eval = new Evaluator(new CompilerContext(settings, printer));
            eval.ReferenceAssembly(typeof(Program).Assembly);
            eval.Run("using System;");
            eval.Run("using managed;");
            eval.Run("dynamic f = new Foo();");
            eval.Run("f.Whatever;");
        }
    }
}
