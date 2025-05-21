using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lb9
{
    public interface IOrderState
    {
        void Proceed(OrderContext context);
        void Cancel(OrderContext context);
        void PrintStatus();
    }
}
